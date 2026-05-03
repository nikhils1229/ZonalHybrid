package zonal_hybrid;

import inet.node.ethernet.EtherSwitch;
import inet.node.ethernet.EtherHost;
import fico4omnet.nodes.can.CanNode;
import fico4omnet.bus.can.CanBus;
import multiprotocol_gateway.MultiGateway;
import lin.LinBus;
import lin.LinNode;
import ned.DatarateChannel;

network ZonalHybridNetwork
{
    parameters:
        @display("bgb=1418,650,white");
        double measure_interval @unit(s) = default(1s);
    types:
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 100ns;
        }
        channel AutomotiveEthernet extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 100ns;
        }

    submodules:
        // ==========================================
        // ZONE 1: Standard CAN (Minimalist)
        // ==========================================
        CAN_Std_Bus: CanBus { @display("i=block/network;p=259,248"); }
        CAN_Std_node: CanNode { @display("p=104,212;i=device/device,green"); }
        
        // ==========================================
        // ZONE 2: CAN-FD (Minimalist)
        // ==========================================
        CAN_FD_Bus_A: CanBus { @display("i=block/network;p=422,478"); }
        CAN_FD_Node_A: CanNode { @display("p=422,574;i=device/device,gold"); }

        CAN_FD_Bus_B: CanBus { @display("i=block/network;p=220,452"); }
        CAN_FD_Node_B: CanNode { @display("p=86,452;i=device/device,gold"); }

        // ==========================================
        // ZONE 3: Automotive Ethernet (Minimalist)
        // ==========================================
        Ethernet_Switch_A: EtherSwitch { @display("i=block/network;p=613,260"); }
        Ethernet_Node_A: EtherHost { @display("p=773,261;i=device/pc,blue"); }

        Ethernet_Switch_B: EtherSwitch { @display("i=block/network;p=700,345"); }
        Ethernet_Node_B: EtherHost { @display("p=848,345;i=device/pc,blue"); }

        Ethernet_Switch_C: EtherSwitch { @display("i=block/network;p=613,427"); }
        Ethernet_Node_C: EtherHost { @display("p=751,506;i=device/pc,blue"); }

        // ==========================================
        // ZONE 4: LIN (Expanded Slaves)
        // ==========================================
        LIN_Master: LinBus { @display("p=600,120;i=block/network,purple"); }
        LIN_Slave_A: LinNode { @display("p=750,60;i=device/device,purple"); }
        LIN_Slave_B: LinNode { @display("p=780,120;i=device/device,purple"); }
        LIN_Slave_C: LinNode { @display("p=750,180;i=device/device,purple"); }

        // ==========================================
        // GATEWAYS & CENTRAL BACKBONE
        // ==========================================
        Gateway_1: MultiGateway {
            parameters:
                numCanPorts = 1; numEthPorts = 1;
                @display("p=324,299;i=device/router,green");
        }
        Gateway_2: MultiGateway {
            parameters:
                numCanFdPorts = 2; numEthPorts = 1;
                @display("p=324,427;i=device/router,gold");
        }
        Gateway_3: MultiGateway {
            parameters:
                numEthPorts = 4; @display("p=560,345;i=device/router,blue");
        }
        Gateway_4: MultiGateway {
            parameters:
                numLinPorts = 1; numEthPorts = 1;
                @display("p=449,120;i=device/router,purple");
        }
        Central_Switch: EtherSwitch { parameters: @display("p=449,345"); }

    connections allowunconnected:
        // Zone 1
        CAN_Std_Bus.gate++ <--> CAN_Std_node.gate;
        Gateway_1.canPort[0] <--> CAN_Std_Bus.gate++;
        Gateway_1.ethg[0] <--> cable <--> Central_Switch.ethg++;

        // Zone 2
        CAN_FD_Bus_A.gate++ <--> CAN_FD_Node_A.gate;
        CAN_FD_Bus_B.gate++ <--> CAN_FD_Node_B.gate;
        Gateway_2.canFdPort[0] <--> CAN_FD_Bus_A.gate++;
        Gateway_2.canFdPort[1] <--> CAN_FD_Bus_B.gate++;
        Gateway_2.ethg[0] <--> cable <--> Central_Switch.ethg++;

        // Zone 3
        Ethernet_Switch_A.ethg++ <--> AutomotiveEthernet <--> Ethernet_Node_A.ethg;
        Ethernet_Switch_B.ethg++ <--> AutomotiveEthernet <--> Ethernet_Node_B.ethg;
        Ethernet_Switch_C.ethg++ <--> AutomotiveEthernet <--> Ethernet_Node_C.ethg;
        Gateway_3.ethg[0] <--> AutomotiveEthernet <--> Ethernet_Switch_A.ethg++;
        Gateway_3.ethg[1] <--> AutomotiveEthernet <--> Ethernet_Switch_B.ethg++;
        Gateway_3.ethg[2] <--> AutomotiveEthernet <--> Ethernet_Switch_C.ethg++;
        Gateway_3.ethg[3] <--> cable <--> Central_Switch.ethg++;

        // Zone 4: Expanded LIN Master-Slave connections
        LIN_Master.gate++ <--> LIN_Slave_A.gate;
        LIN_Master.gate++ <--> LIN_Slave_B.gate;
        LIN_Master.gate++ <--> LIN_Slave_C.gate;
        LIN_Master.gate++ <--> Gateway_4.linPort[0];
        Gateway_4.ethg[0] <--> cable <--> Central_Switch.ethg++;
}
