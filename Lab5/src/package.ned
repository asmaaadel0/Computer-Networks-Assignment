package lab5;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=258,167");
    submodules:
        sender: Sender {
            @display("p=56,78");
        }
        receiver: Receiver {
            @display("p=186,78");
        }
    connections:
        receiver.out --> sender.in;
        sender.out --> receiver.in;
}

