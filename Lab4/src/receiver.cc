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

#include "receiver.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
}

void Receiver::handleMessage(cMessage *msg)
{
    if (msg->getKind() == 0) {
        const char *receivedString = msg->getName();
        std::vector<std::bitset<8>> convertedBits = convertToVector(receivedString);

        bool hasError = checkForErrors(convertedBits);

        if (hasError) {
            EV << "Received message contains errors. Discarding it." << endl;
        } else {
            std::string originalMessage = processReceivedMessage(convertedBits);
            EV << "Received original message: " << originalMessage << endl;
        }
    }

    delete msg;
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

bool Receiver::checkForErrors(std::vector<std::bitset<8>> convertedBits)
{
    std::bitset<8> calculatedParity = convertedBits[0];
    for (size_t i = 1; i < convertedBits.size()-1; ++i) {
        calculatedParity ^= convertedBits[i];
    }

    return calculatedParity != convertedBits.back();
}

std::string Receiver::processReceivedMessage(std::vector<std::bitset<8>> convertedBits)
{
    std::string vectorAsString;
    for (size_t i = 1; i < convertedBits.size()-1; ++i) {
        vectorAsString += convertedBits[i].to_ulong();
    }
    return vectorAsString;
}
