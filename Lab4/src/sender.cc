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

#include "sender.h"
#include <bitset>
#include <vector>
#include <random>

Define_Module(Sender);

void Sender::initialize()
{
    std::string userInput;

    std::cout << "Enter a string: ";
    std::cin >> userInput;

    EV << "message '" << userInput << "':" << endl;


    std::vector<std::bitset<8>> v = convertToVector(userInput);

    std::bitset<8> result(v[0]);

    for (size_t i = 1; i < v.size(); ++i) {
        result ^= v[i];
    }

    v.push_back(result);

    for (const std::bitset<8>& bits : v) {
        EV << bits << endl;
    }

    std::vector<std::bitset<8> > VectorAfterError = generateError(v);

    std::string vectorAsString = convertToString(VectorAfterError);

    cMessage *message = new cMessage("VectorMessage");
    message->setKind(0);
    message->setName(vectorAsString.c_str());

    send(message, "out");
}

std::string Sender::convertToString(std::vector<std::bitset<8>> vectorBits)
{
    std::string vectorAsString;
    for (const std::bitset<8>& bits : vectorBits) {
        vectorAsString += bits.to_string();
        vectorAsString += " ";
    }
    return vectorAsString;
}

std::vector<std::bitset<8>> Sender::generateError(std::vector<std::bitset<8>> v)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 7);

    if (rand() % 2 == 0) {
        int position = distribution(gen);
        int elementToModify = rand() % v.size();
        v[elementToModify].flip(position);
        EV << "There is a modification in element index = " << elementToModify << " bit position index = " << position << endl;
        EV << "New bits : " << endl;
        for (const std::bitset<8>& bits : v) {
            EV << bits << endl;
        }
    }
    return v;
}

std::vector<std::bitset<8>> Sender::convertToVector(std::string userInput)
{
    int length = userInput.length() + 2;

    std::vector<std::bitset<8> > v;

    v.push_back(std::bitset<8>(length));

    for (char c : userInput) {
        std::bitset<8> binaryChar(c);
        v.push_back(binaryChar);
    }
    return v;
}

void Sender::handleMessage(cMessage *msg)
{
    std::string userInput;

    std::cout << "Enter a string: ";
    std::cin >> userInput;

    EV << "message '" << userInput << "':" << endl;


    std::vector<std::bitset<8>> v = convertToVector(userInput);

    std::bitset<8> result(v[0]);

    for (size_t i = 1; i < v.size(); ++i) {
        result ^= v[i];
    }

    v.push_back(result);

    for (const std::bitset<8>& bits : v) {
        EV << bits << endl;
    }

    std::vector<std::bitset<8> > VectorAfterError = generateError(v);

    std::string vectorAsString = convertToString(VectorAfterError);

    cMessage *message = new cMessage("VectorMessage");
    message->setKind(0);
    message->setName(vectorAsString.c_str());

    send(message, "out");
}
