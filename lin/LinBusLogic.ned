package lin;

simple LinBusLogic
{
    parameters:
        double baudRate @unit(bps) = default(19200bps);
        double propDelay @unit(s) = default(0.0001s);
        double interByteTime @unit(s) = default(0.0001s);

        // NEW: Error injection probabilities
        double frameErrorRate = default(0); 
        double frameDropRate = default(0);

        int numGates;
    gates:
        inout gate[numGates];
}
