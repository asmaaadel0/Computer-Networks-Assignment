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

#include "Node.h"


Define_Module(Node);

void Node::initialize()
{

    messageCounter = 0;
    cMessage *msg = new cMessage();
    if(strcmp(getName(), "Tic") == 0)
    {
        sprintf(newName, "Tic_%d", messageCounter);
        msg->setName(newName);
        EV << "Initial message is: " << msg->getName() << endl;
        send(msg->dup(), "out");
        messageCounter ++;
    }
}

void Node::handleMessage(cMessage *msg)
{
    messageCounter ++;

    if (messageCounter > 9)
    {
        EV << "Last message sent. Ending simulation." << endl;
        endSimulation();  // End the simulation when the last message is sent
    }
    else
    {
        if(strcmp(getName(), "Tic") == 0)
        {
            sprintf(newName, "Tic_%d", messageCounter);
        }
        else
        {
            sprintf(newName, "Toc_%d", messageCounter);
        }

        msg->setName(newName);
        send(msg->dup(), "out");
        EV << "Modified message: " << msg->getName() << endl;

        messageCounter ++;
    }

}
