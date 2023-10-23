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
    EV << "Starting Node " << getIndex() << endl;

    if (getIndex() == 0) {
        cMessage *exploreMsg = new cMessage("Explore");
        exploreMsg->setKind(0);
        EV << "Node 0 send message to node 1 " << endl;
        send(exploreMsg, "port$o", 0);
    }
}

void Node::handleMessage(cMessage *msg)
{
    EV << " received message: " << msg->getName() << endl;
    msg->setKind( msg->getKind()+1 );

    if (getIndex() == 0) {
        EV << "Exploration phase completed. Number of connected nodes: " << msg->getKind() << endl;
        delete msg;
        endSimulation();

    } else {
        EV << "Node " << getIndex() <<  " send message" << endl;
        send(msg, "port$o", 1);
    }
}
