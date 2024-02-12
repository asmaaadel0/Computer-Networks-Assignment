package lab2;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=517,222");
    submodules:
        player1: Player1 {
            @display("p=272,83");
        }
        player2: Player2 {
            @display("p=271,160;b=93,24,rect,grey,black");
        }
    connections:
        player1.signal --> player2.signal;
        player2.guess --> player1.guess;
}

