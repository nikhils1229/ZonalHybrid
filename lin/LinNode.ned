package lin;

simple LinNode
{
    parameters:
        bool isMaster = default(false);

        int nodeAddress = default(-1);

        // --- SCHEDULE CONFIGURATION (MASTER ONLY) ---
        string scheduleConfiguration = default("");
        string collisionScheduleConfiguration = default("");

        // --- MILESTONE 2: EVENT-TRIGGERED FRAME (ETF) CONFIG ---
        string eventFrameConfiguration = default("");
        double eventRearmPeriod @unit(s) = default(-1s);
        double eventProbability = default(1.0);

        // --- SIGNAL CONFIGURATION (ALL NODES) ---
        string signalConfiguration = default("");
        string errorSignalConfiguration = default("");

        // NEW: Per-frame data length configuration
        // Format: "10=2;21=4;22=4;3C=8;20=8"
        // If not specified for a frameId, default is 8.
        string frameDlcConfiguration = default("");

        // --- PHY LAYER PARAMETERS ---
        double baudRate @unit(bps) = default(19200bps);
        double propDelay @unit(s) = default(0.0001s);
        double interByteTime @unit(s) = default(0.0001s);

        // NEW: break timing (explicit delimiter)
        int breakBits = default(13);
        int delimiterBits = default(1);

        // --- WAKEUP TEST PARAMETER ---
        double wakeupTime @unit(s) = default(-1s);

        // --- MILESTONE 3: INACTIVITY-BASED SLEEP ---
        double inactivitySleepTime @unit(s) = default(4s);

    gates:
        inout gate;
}
