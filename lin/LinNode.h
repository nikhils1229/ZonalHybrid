#ifndef LINNODE_H_
#define LINNODE_H_

#include <omnetpp.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include "LinDataFrame_m.h"

using namespace omnetpp;

enum LinNodeState {
    IDLE,
    WAIT_FOR_SYNC,
    WAIT_FOR_PID,
    TRANSMITTING,
    RECEIVING,
    SLEEP
};

/*
 * =========================
 * LIN DIAGNOSTICS EXTENSIONS
 * =========================
 *
 * Phase 1: Infrastructure only.
 * No behavioral impact yet.
 */

// Diagnostic frame IDs (RAW IDs, parity added later)
constexpr int LIN_DIAG_MASTER_REQUEST_ID = 0x3C;
constexpr int LIN_DIAG_SLAVE_RESPONSE_ID = 0x3D;

// Diagnostic node role (logical, not a node type)
enum LinDiagRole {
    DIAG_NONE,     // diagnostics disabled
    DIAG_MASTER,  // diagnostic tester
    DIAG_SLAVE    // diagnostic responder
};

// Diagnostic transport protocol state
enum LinDiagTpState {
    DIAG_TP_IDLE,
    DIAG_TP_RX_IN_PROGRESS,
    DIAG_TP_TX_IN_PROGRESS,
    DIAG_TP_WAIT_FC
};

// Diagnostic transport context (per node)
struct LinDiagContext {
    bool enabled = false;
    LinDiagRole role = DIAG_NONE;

    LinDiagTpState tpState = DIAG_TP_IDLE;

    // Transport protocol sequencing
    uint8_t expectedSeq = 0;
    uint8_t nextTxSeq = 0;

    // Reassembly buffer for RX
    std::vector<uint8_t> rxBuffer;
    uint16_t expectedLength = 0;

    // Pending TX payload (multi-frame)
    std::vector<uint8_t> txBuffer;
    uint16_t txOffset = 0;

    // Addressing (NAD / logical address)
    uint8_t targetAddress = 0xFF;   // 0x7F = broadcast in LIN diag
    uint8_t sourceAddress = 0x00;

    // Timeout handling
    simtime_t lastActivity;
};

/*
 * =========================
 * EXISTING DATA STRUCTURES
 * =========================
 */

struct LinSlot {
    int frameId;
    std::string publisher;
    double period;
    bool isETF = false;
};

struct LinSignal {
    int frameId;
    int byteOffset;
    int value;
};

struct LinErrorSignalBinding {
    int frameId;
    int byteOffset;
    int bitIndex;
};

struct LinErrorState {
    bool lastHeaderError = false;
    bool lastChecksumError = false;
    bool lastTimeoutError = false;
};

class LinNode : public cSimpleModule
{
private:
    bool isMaster;
    int nodeAddress;
    LinNodeState state;

    // =========================
    // DIAGNOSTICS (INACTIVE)
    // =========================
    LinDiagContext diagCtx;

    // --- TIMERS ---
    cMessage *scheduleTimer;
    cMessage *headerTimer;
    cMessage *responseTimeoutTimer;

    cMessage *wakeupTimer;
    cMessage *wakeupExpirationTimer;

    cMessage *goToSleepTimer;

    cMessage *eventRearmTimer;

    cMessage *inactivityTimer;
    double inactivitySleepTime = 4.0;

    int pendingResponseFrameId = -1;
    bool scheduleRunning = true;

    // --- RX QUALIFICATION ---
    bool rxSawBreak = false;
    bool rxAwaitingResponse = false;
    int  rxExpectedResponseId = -1;

    // --- WAKEUP LOGIC STATE ---
    int wakeupRetryCount = 0;
    bool pendingWakeup = false;

    // --- PHY PARAMETERS ---
    double baudRate;
    double propDelay;
    double interByteTime;

    // NEW: break/delimiter timing knobs
    int breakBits = 13;
    int delimiterBits = 1;

    // --- DLC CONFIG ---
    std::unordered_map<int,int> frameIdToDlc;

    // --- SCHEDULE TABLES ---
    std::vector<LinSlot> scheduleTable;
    int currentSlotIndex = 0;

    std::vector<LinSlot> collisionScheduleTable;
    bool resolvingCollision = false;
    int collisionSlotIndex = 0;

    LinSlot pendingHeaderSlot;
    bool pendingHeaderValid = false;
    bool endResolveAfterHeader = false;

    // --- SIGNALS & ERROR MAPPING ---
    std::vector<LinSignal> signalTable;
    std::vector<LinErrorSignalBinding> errorBindings;
    LinErrorState errorState;

    // --- ETF MAP + EVENT FLAGS ---
    std::unordered_map<int, std::vector<int>> etfToUcfs;
    std::unordered_map<int, bool> ucfEventPending;

    double eventRearmPeriod = -1;
    double eventProbability = 1.0;

    // --- HELPERS ---
    void parseSchedule(const char* config, std::vector<LinSlot>& table);
    void parseSignals(const char* config);
    void parseErrorSignals(const char* config);

    // DLC
    void parseFrameDlcs(const char* config);
    int dlcForFrame(int frameId) const;

    // ETF
    void parseEventFrames(const char* config);
    void initializeEventFlags();
    bool isEventFrameId(int etfId) const;
    bool selectUcfForEventFrame(int etfId, int& outUcfId) const;
    void setEventPending(int ucfId, bool pending);

    // Sleep/Inactivity
    void resetInactivityTimer();
    void enterSleep(const char *reason);

    // RX context
    void resetRxContext();

    bool isPublisherFor(int frameId);
    void applyErrorBits(int logicalFrameId, LinResponse *rsp, int payloadBase);
    bool isGoToSleepCommand(const LinResponse *rsp) const;

    // Timing helpers
    double headerRemainderTxTime() const;
    double responseTxTime(int dataLength) const;

    // --- PROTOCOL ACTIONS ---
    void sendBreakSignal();
    void sendWakeupPulse();
    void sendHeaderRemainder(int frameId, std::string publisher);

    void sendResponse(int frameId, double initialDelay);
    void sendEventResponse(int etfId, int ucfId, double initialDelay);

    void processReceivedHeader(LinHeader *header);

    void startCollisionResolution();
    bool isWakeupPulse(LinBreakSignal *brk);

    bool isEchoFromSelf(int sourceAddr) const {
        return (nodeAddress >= 0 && sourceAddr == nodeAddress);
    }

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif
