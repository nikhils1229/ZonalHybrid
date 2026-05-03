package multiprotocol_gateway;

import inet.node.ethernet.EtherSwitch;
import inet.node.ethernet.EtherHost;
import fico4omnet.nodes.can.CanNode;
import fico4omnet.bus.can.CanBus;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import ned.DatarateChannel;

network Testbed
{
    parameters:
        @display("bgb=800,600");

    types:
        // Automotive Ethernet strictly requires Point-to-Point, Full-Duplex over a single twisted pair (100BASE-T1 / 1000BASE-T1).
        channel AutomotiveEthernetChannel extends DatarateChannel {
            datarate = 100Mbps; // 100BASE-T1
            delay = 0.5us;      // ~100m max cable delay
        }

    submodules:
        gateway: MultiGateway {
            parameters:
                numCanPorts = 1;
                numCanFdPorts = 1;
                numEthPorts = 1;
                numLinPorts = 1;
                @display("p=400,300");
        }
        
        canBus: CanBus { @display("p=200,400"); }
        canFdBus: CanBus { @display("p=600,400"); }

        canNode: CanNode { @display("p=100,450"); }
        canFdNode: CanNode { @display("p=700,450"); }
        
        ethSwitch: EtherSwitch { @display("p=400,150"); }
        ethNode: EtherHost { @display("p=400,50"); }

    connections allowunconnected:
        canNode.gate <--> canBus.gate++;
        gateway.canPort[0] <--> canBus.gate++;
        
        canFdNode.gate <--> canFdBus.gate++;
        gateway.canFdPort[0] <--> canFdBus.gate++;

        // Point-to-Point full-duplex links simulating Automotive Ethernet physical layer
        gateway.ethg[0] <--> AutomotiveEthernetChannel <--> ethSwitch.ethg++;
        ethSwitch.ethg++ <--> AutomotiveEthernetChannel <--> ethNode.ethg;
}
