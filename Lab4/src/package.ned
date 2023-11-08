package lab4;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=264,171");
    submodules:
        sender: Sender {
            @display("p=39,80");
        }
        receiver: Receiver {
            @display("p=219,80");
        }
    connections:
        sender.out --> receiver.in;
        receiver.out --> sender.in;
}

