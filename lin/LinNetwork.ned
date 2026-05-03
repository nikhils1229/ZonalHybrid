package lin;

network LinNetwork
{
    parameters:
        int numSlaves = default(2);

    submodules:
        bus: LinBusLogic {
            parameters:
                numGates = 1 + parent.numSlaves;
                baudRate = 19200bps;
                propDelay = 0.0001s;
                interByteTime = 0.0001s;
                @display("p=100,100;t=LINbus");
        }

        master: LinNode {
            parameters:
                isMaster = true;
                nodeAddress = 0; // NEW
                baudRate = 19200bps;
                propDelay = 0.0001s;
                interByteTime = 0.0001s;
                @display("p=100,200;t=Master");
        }

        slaves[numSlaves]: LinNode {
            parameters:
                isMaster = false;
                nodeAddress = index + 1; // NEW
                baudRate = 19200bps;
                propDelay = 0.0001s;
                interByteTime = 0.0001s;
                @display("p=200,200,row,80;t=Slave");
        }

    connections:
        master.gate <--> bus.gate[0];

        for i=0..numSlaves-1 {
            slaves[i].gate <--> bus.gate[i+1];
        }
}
