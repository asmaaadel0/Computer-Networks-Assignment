package lab3;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    parameters:
        int N = default(4);
    @display("bgb=528,311");
    submodules:
        Router: Router ;
        nodes[N]: Node ;
        
    connections:
        for i=0..N-1 {
            Router.port++ <--> nodes[i].port++;
        }    
}

