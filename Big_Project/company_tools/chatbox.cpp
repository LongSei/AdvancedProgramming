#include"./company_tools/chatbox.hpp"
using namespace std;

void ChatBox::init() {
    messageMemory.clear();
}

void ChatBox::inviteMember(Characters* emp) {
    isMember[emp] = true;
}

void ChatBox::removeMember(Characters* emp) {
    isMember[emp] = false;
}

bool ChatBox::canMessage(Characters* emp) {
    return isMember[emp];
}   

void ChatBox::appendMessage(Characters* emp, string message) {
    messageMemory.push_back(pair<Characters*, string>(emp, message));
}