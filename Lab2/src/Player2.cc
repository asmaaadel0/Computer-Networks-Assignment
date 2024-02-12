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

#include "Player2.h"

Define_Module(Player2);

void Player2::initialize()
{
}

void Player2::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "start guessing") == 0 || strcmp(msg->getName(), "wrong guess") == 0)
     {
        cMessage *guessMsg = new cMessage("guess");
        guessMsg->setName(std::to_string(int(par("guessingNumber"))).c_str());
        send(guessMsg, "guess");
     }
    else if (strcmp(msg->getName(), "correct guess") == 0)
    {
        EV << "success!" << endl;
        cancelAndDelete(msg);
    }
}
