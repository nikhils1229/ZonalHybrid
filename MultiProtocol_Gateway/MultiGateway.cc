#include "MultiGateway.h"
#include "lin/LinUtil.h"
#include "inet/linklayer/ethernet/EtherFrame.h"
#include "inet/applications/ethernet/EtherApp_m.h"

namespace multiprotocol_gateway {

Define_Module(MultiGateway);

void MultiGateway::initialize() {
  enableFragmentation = par("enableFragmentation").boolValue();
  enableAggregation = par("enableAggregation").boolValue();
  processingDelay = par("processingDelay").doubleValue();
  maxQueueSize = par("maxQueueSize").intValue();

  droppedCorruptedCount = 0;
  bufferOverflowCount = 0;

  txTimer = new cMessage("txTimer");
  aggregationTimer = new cMessage("aggregationTimer");
  ethTxTimer = new cMessage("ethTxTimer");
  linTxTimer = new cMessage("linTxTimer");
}

MultiGateway::~MultiGateway() {
  cancelAndDelete(txTimer);
  cancelAndDelete(aggregationTimer);
  cancelAndDelete(ethTxTimer);
  cancelAndDelete(linTxTimer);
  
  while (!pendingCanFragments.empty()) {
    delete pendingCanFragments.top();
    pendingCanFragments.pop();
  }
  for (auto p : pendingEthFrames) delete p.second;
}

void MultiGateway::handleMessage(cMessage *msg) {
  if (msg == txTimer) {
    sendNextFragment();
    return;
  }

  if (msg == ethTxTimer) {
      sendNextEthFrame();
      return;
  }

  if (msg == linTxTimer) {
      sendNextLinPoll();
      return;
  }

  if (msg == aggregationTimer) {
    for (auto const& [port, buffer] : aggregationBuffers) {
        if (!buffer.empty()) {
            sendAggregatedEth(port);
        }
    }
    return;
  }

  if (msg->isSelfMessage()) {
      delete msg;
      return;
  }

  std::string gateName = msg->getArrivalGate()->getBaseName();

  if (gateName == "canPort" || gateName == "canFdPort") {
    processCanFrame(msg);
  } else if (gateName == "ethg") {
    processEthFrame(msg);
  } else if (gateName == "linPort") {
    processLinFrame(msg);
  } else {
    delete msg;
  }
}

void MultiGateway::processCanFrame(cMessage *msg) {
  FiCo4OMNeT::CanDataFrame *canFrame =
      dynamic_cast<FiCo4OMNeT::CanDataFrame *>(msg);
  if (!canFrame) {
    delete msg;
    return;
  }

  if (canFrame->hasBitError()) {
    droppedCorruptedCount++;
    delete msg;
    return;
  }

  EV << "Received CAN frame ID: " << canFrame->getCanID() << " (" << (canFrame->isCanFd() ? "FD" : "Std") << ")\n";

  RouteEntity route;
  if (routingTable.lookupCanRoute(canFrame->getCanID(), route)) {
    std::vector<uint8_t> payload;
    for (unsigned int i = 0; i < canFrame->getPayloadArraySize(); i++) {
      payload.push_back(canFrame->getPayload(i));
    }

    if (route.targetProto == Protocol::ETHERNET) {
      if (enableAggregation) {
          auto& buffer = aggregationBuffers[route.targetPort];
          buffer.insert(buffer.end(), payload.begin(), payload.end());
          
          if (buffer.size() >= 64) {
              sendAggregatedEth(route.targetPort);
          } else if (!aggregationTimer->isScheduled()) {
              scheduleAt(simTime() + 0.0005, aggregationTimer);
          }
      } else {
          packToEth(route.targetPort, payload);
      }
    } else if (route.targetProto == Protocol::CAN || route.targetProto == Protocol::CAN_FD) {
      packToCan(route.targetPort, payload, route.targetProto == Protocol::CAN_FD);
    } else if (route.targetProto == Protocol::LIN) {
      packToLin(0, payload, route.targetId);
    }
  }
  delete msg;
}

void MultiGateway::sendAggregatedEth(int port) {
    std::vector<uint8_t> payload = aggregationBuffers[port];
    aggregationBuffers[port].clear();
    packToEth(port, payload);
}

void MultiGateway::processEthFrame(cMessage *msg) {
  EV << "Received Ethernet Frame from Backbone\n";
  std::vector<uint8_t> mockPayload(64, 0xBB);

  if (gate("canPort$o", 0)->isConnected()) {
      EV << " -> Routing backbone payload to Standard CAN (ID: 110)\n";
      packToCan(0, mockPayload, false);
  }

  if (gate("canFdPort$o", 0)->isConnected()) {
      EV << " -> Routing backbone payload to CAN-FD (ID: 220)\n";
      packToCan(0, mockPayload, true);
  }

  if (gate("linPort$o", 0)->isConnected()) {
      // Demo Veracity: Poll LIN Slaves sequentially
      pendingLinPolls.push_back(0x30);
      pendingLinPolls.push_back(0x31);
      pendingLinPolls.push_back(0x32);
      
      if (!linTxTimer->isScheduled()) {
          scheduleAt(simTime(), linTxTimer);
      }
  }
  
  delete msg;
}

void MultiGateway::processLinFrame(cMessage *msg) {
  LinResponse *rsp = dynamic_cast<LinResponse *>(msg);
  if (rsp) {
      EV << "Received LIN Response (ID: 0x" << std::hex << rsp->getFrameId() << std::dec << ")\n";
      std::vector<uint8_t> payload;
      for (int i = 0; i < rsp->getDataLength(); i++) {
          payload.push_back(rsp->getData(i));
      }
      packToEth(0, payload);
  }
  delete msg;
}

void MultiGateway::packToEth(int destEthPort, const std::vector<uint8_t> &payload) {
  inet::EthernetIIFrame *ethFrame = new inet::EthernetIIFrame("EthFwd");
  ethFrame->setSrc(inet::MACAddress("02-00-00-00-00-01"));
  ethFrame->setDest(inet::MACAddress::BROADCAST_ADDRESS); 
  ethFrame->setEtherType(0xAAAA); 

  inet::EtherAppReq *appReq = new inet::EtherAppReq("CAN-to-Eth");
  appReq->setByteLength(payload.size());
  ethFrame->encapsulate(appReq);

  inet::EtherPhyFrame *phyFrame = new inet::EtherPhyFrame("EthPhyFwd");
  phyFrame->setSrcMacFullDuplex(true); 
  phyFrame->encapsulate(ethFrame);

  EV << "[Aggregation] Mapped " << (payload.size() > 8 ? "FD" : "Std") 
     << " to Ethernet on port " << destEthPort 
     << " with payload size " << payload.size() << "\n";

  pendingEthFrames.push_back({destEthPort, phyFrame});
  if (!ethTxTimer->isScheduled()) {
      scheduleAt(simTime(), ethTxTimer);
  }
}

void MultiGateway::sendNextEthFrame() {
    if (pendingEthFrames.empty()) return;

    auto next = pendingEthFrames.front();
    int port = next.first;
    inet::EtherPhyFrame *frame = next.second;

    cGate *outGate = gate("ethg$o", port);
    cChannel *txChannel = outGate->getTransmissionChannel();
    simtime_t txFinishTime = txChannel ? txChannel->getTransmissionFinishTime() : simTime();

    if (simTime() < txFinishTime) {
        scheduleAt(txFinishTime, ethTxTimer);
        return;
    }

    pendingEthFrames.pop_front();
    sendDelayed(frame, processingDelay, outGate);

    if (!pendingEthFrames.empty()) {
        scheduleAt(outGate->getTransmissionChannel()->getTransmissionFinishTime() + 1e-9, ethTxTimer);
    }
}

void MultiGateway::packToLin(int destLinPort, const std::vector<uint8_t> &payload, int linId) {
    // Logic moved to sendNextLinPoll to ensure sequential bus access
    pendingLinPolls.push_back(linId);
    if (!linTxTimer->isScheduled()) {
        scheduleAt(simTime(), linTxTimer);
    }
}

void MultiGateway::sendNextLinPoll() {
    if (pendingLinPolls.empty()) return;

    int linId = pendingLinPolls.front();
    pendingLinPolls.pop_front();

    EV << "[LIN MASTER] Initiating Polling Transaction for ID 0x" << std::hex << linId << std::dec << "\n";

    // 1. Send Break
    LinBreakSignal *brk = new LinBreakSignal("LIN_Break");
    brk->setSourceAddr(100); 
    brk->setDuration(13.0 / 20000.0); 
    send(brk, "linPort$o", 0);

    // 2. Send Header (Staggered to match physical bit times at 20kbps)
    LinHeader *hdr = new LinHeader("LIN_Header");
    hdr->setSourceAddr(100);
    hdr->setFrameId(linId);
    hdr->setPid(computePID(linId));
    sendDelayed(hdr, 0.001, "linPort$o", 0);

    // 3. Schedule next poll after this transaction finishes (~15ms for safety)
    if (!pendingLinPolls.empty()) {
        scheduleAt(simTime() + 0.015, linTxTimer);
    }
}

void MultiGateway::packToCan(int destCanPort, const std::vector<uint8_t> &payload, bool isCanFd) {
  cGate *outGate = nullptr;
  try {
      outGate = gate(isCanFd ? "canFdPort$o" : "canPort$o", destCanPort);
      if (!outGate->isConnected()) return;
  } catch (std::exception& e) {
      return;
  }

  unsigned int maxLen = isCanFd ? 64 : 8;
  unsigned int fragments = (payload.size() + maxLen - 1) / maxLen;

  EV << "[Segmentation] Routing to " << (isCanFd ? "CAN-FD" : "Std CAN") 
     << " Port " << destCanPort << " (" << fragments << " fragments)\n";

  for (unsigned int i = 0; i < payload.size(); i += maxLen) {
    FiCo4OMNeT::CanDataFrame *frag = new FiCo4OMNeT::CanDataFrame("Fragment");
    frag->setCanID(isCanFd ? 220 : 110);
    frag->setIsCanFd(isCanFd);
    frag->setBrs(isCanFd);
    
    unsigned int len = std::min(maxLen, (unsigned int)payload.size() - i);
    frag->setPayloadArraySize(len);
    for (unsigned int j = 0; j < len; j++) {
      frag->setPayload(j, payload[i + j]);
    }
    
    pendingCanFragments.push(frag);
  }

  if (!txTimer->isScheduled()) {
    scheduleAt(simTime() + 0.0001, txTimer);
  }
}

void MultiGateway::sendNextFragment() {
  if (pendingCanFragments.empty())
    return;

  FiCo4OMNeT::CanDataFrame *fwdMsg = pendingCanFragments.top();
  pendingCanFragments.pop();

  const char* gateName = fwdMsg->isCanFd() ? "canFdPort$o" : "canPort$o";
  if (gate(gateName, 0)->isConnected()) {
      send(fwdMsg, gateName, 0);
  } else {
      delete fwdMsg;
  }

  if (!pendingCanFragments.empty()) {
    scheduleAt(simTime() + 0.001, txTimer);
  }
}

} // namespace multiprotocol_gateway
