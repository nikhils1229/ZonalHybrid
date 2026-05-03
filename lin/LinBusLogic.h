#ifndef LINBUSLOGIC_H_
#define LINBUSLOGIC_H_

#include <omnetpp.h>
#include "LinDataFrame_m.h"

using namespace omnetpp;

class LinBusLogic : public cSimpleModule {
    double baudRate;
    double propDelay;
    double interByteTime;

    double frameErrorRate;
    double frameDropRate;

    // Response-window tracking (for collision modelling)
    bool isResponseOnBus;
    cMessage *transmissionEndTimer;

    // Hold first response until end-of-response so collisions can invalidate it
    LinResponse *pendingResponse;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

private:
    // Nominal durations (seconds) derived from LIN UART-style framing
    // Header remainder = Sync(1 byte) + PID(1 byte) => 2 bytes => 20 bits (10 bits/byte)
    double headerRemainderTxTime() const;

    // Response = N data bytes + 1 checksum byte => (N+1) bytes => (N+1)*10 bits
    double responseTxTime(int dataLength) const;

    void forwardToAll(cPacket *frame, simtime_t extraDelay);
};

#endif
