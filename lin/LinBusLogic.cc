#include "LinBusLogic.h"
#include "LinDataFrame_m.h"
#include <omnetpp.h>

Define_Module(LinBusLogic);

void LinBusLogic::initialize() {
    EV_INFO << "LIN bus initialized (Timed forwarder + collision model)" << endl;

    baudRate = par("baudRate");
    propDelay = par("propDelay");
    interByteTime = par("interByteTime");

    frameErrorRate = par("frameErrorRate");
    frameDropRate  = par("frameDropRate");

    isResponseOnBus = false;
    transmissionEndTimer = new cMessage("txEnd");

    pendingResponse = nullptr;
}

void LinBusLogic::finish() {
    cancelAndDelete(transmissionEndTimer);
    transmissionEndTimer = nullptr;

    if (pendingResponse) {
        delete pendingResponse;
        pendingResponse = nullptr;
    }
}

double LinBusLogic::headerRemainderTxTime() const {
    const int bits = 2 * 10; // Sync + PID, 10 bits each (UART style)
    return (double)bits / baudRate;
}

double LinBusLogic::responseTxTime(int dataLength) const {
    int n = dataLength;
    if (n < 0) n = 0;
    if (n > 8) n = 8;
    const int bytes = n + 1; // + checksum
    const int bits = bytes * 10;
    return (double)bits / baudRate;
}

void LinBusLogic::forwardToAll(cPacket *frame, simtime_t extraDelay) {
    int gateCount = gateSize("gate$o");
    for (int i = 0; i < gateCount; i++) {
        cPacket *out = (i == gateCount - 1) ? frame : frame->dup();
        sendDelayed(out, extraDelay, "gate$o", i);
    }
}

void LinBusLogic::handleMessage(cMessage *msg) {
    EV_INFO << "Bus received message: " << msg->getName() << " from gate index " << (msg->getArrivalGate() ? msg->getArrivalGate()->getIndex() : -1) << endl;
    // --- 1) SELF-MESSAGE: end of response window ---
    if (msg == transmissionEndTimer) {
        EV_DETAIL << "Bus: Response window ended. Bus is now free." << endl;
        isResponseOnBus = false;

        if (pendingResponse) {
            EV_INFO << "Bus forwarding signal: " << pendingResponse->getName()
                    << " (" << pendingResponse->getBitLength() << " bits)" << endl;

            forwardToAll(pendingResponse, propDelay);
            pendingResponse = nullptr;
        }
        return;
    }

    // --- 2) Determine which port injected the signal ---
    int srcGateIndex = -1;
    if (msg->getArrivalGate() != nullptr) {
        srcGateIndex = msg->getArrivalGate()->getIndex();
    }

    // --- 3) Cast to packet ---
    cPacket *frame = check_and_cast<cPacket *>(msg);

    // --- 4) Record ingress port index (DO NOT overwrite sender identity) ---
    if (auto brk = dynamic_cast<LinBreakSignal*>(frame)) {
        brk->setIngressPortIndex(srcGateIndex);
    } else if (auto hdr = dynamic_cast<LinHeader*>(frame)) {
        hdr->setIngressPortIndex(srcGateIndex);
    } else if (auto rsp = dynamic_cast<LinResponse*>(frame)) {
        rsp->setIngressPortIndex(srcGateIndex);
    }

    // --- 5) Sanity: header/break during active response window (schedule bug) ---
    if (isResponseOnBus && dynamic_cast<LinResponse*>(frame) == nullptr) {
        EV_WARN << "Bus received " << frame->getName()
                << " while response window active (schedule/protocol violation in model)." << endl;
    }

    // --- 6) Error injection: drop ---
    if (uniform(0, 1) < frameDropRate) {
        EV_WARN << "Bus DROPPING frame: " << frame->getName() << endl;
        delete frame;
        return;
    }

    // --- 7) Error injection: corrupt ---
    if (uniform(0, 1) < frameErrorRate) {
        EV_WARN << "Bus CORRUPTING frame: " << frame->getName() << endl;

        if (auto rsp = dynamic_cast<LinResponse*>(frame)) {
            int len = rsp->getDataLength();
            if (len > 0) {
                int idx = intuniform(0, len - 1);
                char oldVal = rsp->getData(idx);
                rsp->setData(idx, oldVal ^ 0xFF);
            }
        } else if (auto hdr = dynamic_cast<LinHeader*>(frame)) {
            hdr->setPid(hdr->getPid() ^ 0xFF);
        }
        // Note: break “corruption” is just logged (duration isn’t modified here).
    }

    // --- 8) RESPONSE handling: collision + timed delivery at end-of-response ---
    if (auto rsp = dynamic_cast<LinResponse*>(frame)) {

        if (!isResponseOnBus) {
            isResponseOnBus = true;
            pendingResponse = rsp;

            double txDuration = responseTxTime(rsp->getDataLength());
            scheduleAt(simTime() + txDuration, transmissionEndTimer);
            return;
        }

        EV_WARN << "COLLISION DETECTED on Bus for ID 0x" << std::hex
                << rsp->getFrameId() << std::dec << endl;

        if (pendingResponse) {
            pendingResponse->setCollision(true);
            pendingResponse->setName("LIN_COLLISION");
        }

        delete rsp;
        return;
    }

    // --- 9) HEADER handling: timed delivery at end-of-header remainder ---
    if (auto hdr = dynamic_cast<LinHeader*>(frame)) {
        EV_INFO << "Bus forwarding signal: " << hdr->getName()
                << " (" << hdr->getBitLength() << " bits)" << endl;

        double tx = headerRemainderTxTime();
        forwardToAll(hdr, tx + propDelay);
        return;
    }

    // --- 10) BREAK / others: forward with propagation only ---
    EV_INFO << "Bus forwarding signal: " << frame->getName()
            << " (" << frame->getBitLength() << " bits)" << endl;

    forwardToAll(frame, propDelay);
}
