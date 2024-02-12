package lab1;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=570,280");
    submodules:
        Tic: Node {
            @display("p=94,95");
        }
        Toc: Node {
            @display("p=415,95");
        }
    connections:
        Tic.out --> Toc.in;
        Toc.out --> Tic.in;
}

