//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Player1.h"

Define_Module(Player1);

void Player1::initialize()
{
    EV << "Player1's secret number is: " << int(par("secretNumber")) << endl;

    cMessage *signalMsg = new cMessage("start guessing");
    send(signalMsg, "signal");
}

void Player1::handleMessage(cMessage *msg)
{
    int guess = atoi(msg->getFullName());

    EV << "Player2 guessed: " << guess << endl;

    if (guess == int(par("secretNumber")))
    {
        EV << "Player2 made the correct guess!" << endl;
        msg->setName("correct guess");
        send(msg, "signal");
    }
    else
    {
        EV << "Player2 made a wrong guess." << endl;

        msg->setName("wrong guess");
        send(msg, "signal");
    }
}
