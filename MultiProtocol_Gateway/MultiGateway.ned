package multiprotocol_gateway;

import inet.linklayer.contract.IEtherMac;
import fico4omnet.linklayer.can.CanPort;
// LIN ports will be mocked if FiCo doesn't have explicit LIN yet

// Central Gateway connecting heterogeneous networks
simple MultiGateway
{
    parameters:
        @display("i=device/router");
        int numCanPorts = default(1);
        int numCanFdPorts = default(1);
        int numLinPorts = default(1);
        int numEthPorts = default(1);
        
        bool enableFragmentation = default(true);
        bool enableAggregation = default(true);
        
        // Processing latency models the L7 routing application processing time
        double processingDelay @unit(s) = default(0.001s); // 1ms default processing time
        int maxQueueSize = default(100); // Max packets before Gateway Buffer Overflow
        
    gates:
        inout canPort[numCanPorts];
        inout canFdPort[numCanFdPorts];
        inout linPort[numLinPorts];
        inout ethg[numEthPorts];
}
