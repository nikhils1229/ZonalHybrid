#ifndef __MULTIPROTOCOL_GATEWAY_H_
#define __MULTIPROTOCOL_GATEWAY_H_

#include <queue>
#include <vector>

#include "RoutingTable.h"
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "lin/LinDataFrame_m.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace multiprotocol_gateway {

struct CompareCanPriority {
  bool operator()(const FiCo4OMNeT::CanDataFrame *a,
                  const FiCo4OMNeT::CanDataFrame *b) const {
    // In CAN, a lower ID means higher priority.
    // std::priority_queue keeps the "largest" element at the top.
    // Therefore, we want a > b (so the smaller ID floats to the top of the
    // queue).
    return a->getCanID() > b->getCanID();
  }
};

class MultiGateway : public cSimpleModule {
protected:
  virtual void initialize() override;
  virtual ~MultiGateway();
  virtual void handleMessage(cMessage *msg) override;

  void processCanFrame(cMessage *msg);
  void processEthFrame(cMessage *msg);
  void processLinFrame(cMessage *msg);

  void packToEth(int destEthPort, const std::vector<uint8_t> &payload);
  void packToCan(int destCanPort, const std::vector<uint8_t> &payload,
                 bool isCanFd);
  void packToLin(int destLinPort, const std::vector<uint8_t> &payload,
                 int linId);

private:
  RoutingTable routingTable;
  bool enableFragmentation;
  bool enableAggregation;

  // Latency & Error properties
  double processingDelay;
  unsigned int maxQueueSize;
  unsigned int droppedCorruptedCount;
  unsigned int bufferOverflowCount;

  // Paced Fragmentation Priority Queue (QoS)
  std::priority_queue<FiCo4OMNeT::CanDataFrame *,
                      std::vector<FiCo4OMNeT::CanDataFrame *>,
                      CompareCanPriority>
      pendingCanFragments;
  cMessage *txTimer;

  // Ethernet Queuing (Backbone Pacing)
  std::deque<std::pair<int, inet::EtherPhyFrame *>> pendingEthFrames;
  cMessage *ethTxTimer;
  void sendNextEthFrame();

  // LIN Queuing (Slow Bus Pacing)
  std::deque<int> pendingLinPolls;
  cMessage *linTxTimer;
  void sendNextLinPoll();

  // Aggregation Buffer (CAN -> Ethernet)
  std::map<int, std::vector<uint8_t>> aggregationBuffers;
  cMessage *aggregationTimer;
  void sendAggregatedEth(int port);

  void sendNextFragment();
};

} // namespace multiprotocol_gateway
#endif
