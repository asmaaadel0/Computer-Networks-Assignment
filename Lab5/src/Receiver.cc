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

#include "Receiver.h"
#include "MyMessage_m.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
}

void Receiver::handleMessage(cMessage *msg)
{
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    if(mmsg->getM_Type() == 2) {

        const char *receivedString = mmsg->getM_Payload();
        std::vector<std::bitset<8>> convertedBits = convertToVector(receivedString);

        bool hasError = checkForErrors(convertedBits, mmsg);

        if (hasError) {
            EV << "Received message contains errors. Discarding it." << endl;
            mmsg->setM_Type(1);
            mmsg->setM_Payload("Received with error, Send another one to me");
        } else {
            std::string originalMessage = processReceivedMessage(convertedBits);
            EV << "Received original message: " << originalMessage << endl;
            mmsg->setM_Type(0);
            mmsg->setM_Payload("Received Successfully");
        }
        send(mmsg, "out");
    }
}

std::vector<std::bitset<8>> Receiver::convertToVector(const char *receivedString)
{
    std::istringstream iss(receivedString);
    std::vector<std::bitset<8>> tokens;

    while (iss) {
        std::bitset<8> token;
        iss >> token;

        tokens.push_back(token);
    }
    tokens.pop_back();
    return tokens;
}

bool Receiver::checkForErrors(std::vector<std::bitset<8>> convertedBits, MyMessage_Base* message)
{
    std::bitset<8> calculatedParity (message->getM_Header());
    for (size_t i = 0; i < convertedBits.size(); ++i) {
        calculatedParity ^= convertedBits[i];
    }
    std::bitset<8> trailer (message->getM_Trailer());
    return calculatedParity != trailer;
}

std::string Receiver::processReceivedMessage(std::vector<std::bitset<8>> convertedBits)
{
    std::string vectorAsString;
    for (size_t i = 0; i < convertedBits.size(); ++i) {
        vectorAsString += convertedBits[i].to_ulong();
    }
    return vectorAsString;
}

