package signalsandgateways.examples.canFdNetwork;
// ... (imports remain)
network canFdNetwork
{
    parameters:
        @display("bgb=604,114,white");
    types:
        //
        // All links are configured with 100MBit per second and variable delay
        //
        channel cable extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            //bit error rate (probability (0.0-1.0) per bit)  
            ber = 0;
            //packet error rate (probability (0.0-1.0) per packet)  
            per = 0;
        }
        
    submodules:
        canbus1: CanBus {
            @display("p=137,62");
        }
        canNode1: CanNode {
            @display("p=51,62");
        }
        canbus2: CanBus {
            @display("p=467,62");
        }
        canNode2: CanNode {
            @display("p=553,62");
        }
        gateway1: Gateway1 {
            @display("p=214,62");
            gates:
                cang[1];
                ethg[1];
        }

        gateway2: Gateway2 {
            @display("p=381,62");
            gates:
                cang[1];
                ethg[1];
        }

        switch: Switch {
            parameters:
                @display("p=295,62");
            gates:
                ethg[2];
        }

    connections:
        gateway1.ethg[0] <--> cable {  delay = 100ns; } <--> switch.ethg[0];
        gateway2.ethg[0] <--> cable {  delay = 50ns; } <--> switch.ethg[1];

		gateway1.cang[0] <--> canbus1.gate++;
		gateway2.cang[0] <--> canbus2.gate++;
		
        canbus1.gate++ <--> canNode1.gate;
        canbus2.gate++ <--> canNode2.gate;        
}
