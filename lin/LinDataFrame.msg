cplusplus {{
#include <omnetpp.h>
}}

// 1) The Break field is a physical signal (dominant state), not a data byte.
packet LinBreakSignal {
    // True node identity (set by sender LinNode::nodeAddress)
    int sourceAddr = -1;

    // Bus ingress information (set by LinBusLogic from arrival gate index)
    int ingressPortIndex = -1;

    double duration; // Duration of the dominant state (min 13 bit times)
}

// 2) The Header remainder (Sync + PID) sent by the Master
packet LinHeader {
    int sourceAddr = -1;         // True node identity (sender nodeAddress)
    int ingressPortIndex = -1;   // Bus port index where it entered

    int frameId;      // Useful for simulation logic (metadata)
    int pid;          // Protected Identifier (6-bit ID + 2 parity bits)
    char syncByte = 0x55;
}

// 3) The Response part (Data + Checksum) sent by Publisher (Master or Slave)
packet LinResponse {
    int sourceAddr = -1;         // True node identity (sender nodeAddress)
    int ingressPortIndex = -1;   // Bus port index where it entered

    int frameId;      // Metadata to help receivers match response to header
    int dataLength = 8;
    char data[8];
    char checksum;    // Classic or Enhanced checksum

    // Flag to indicate this response collided on the bus
    bool collision = false;
}
