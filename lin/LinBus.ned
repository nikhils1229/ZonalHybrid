package lin;

module LinBus
{
    parameters:
        @display("i=block/network");
        int numGates = default(3); // number of connected nodes
    gates:
        inout gate[numGates];  // pre-allocate gate array

    submodules:
        logic: LinBusLogic {
            @display("p=100,100");
        }

    connections allowunconnected:
        for i=0..numGates-1 {
            gate[i] <--> logic.gate++;
        }
}
