#include"./company_tools/manager.hpp"
using namespace std;

void Manager::addNewEmployment() {
    Characters* newEmploy = new Characters;
    (*newEmploy).init("None");
    employment.push_back(newEmploy);
}

void Manager::addNewChatBox() {
    ChatBox* newChatBox = new ChatBox;
    (*newChatBox).init();
    chatbox.push_back(newChatBox);
}

void Manager::removeEmployment(Characters* emp) {
    auto it = find(employment.begin(), employment.end(), emp);
    if (it != employment.end()) {
        employment.erase(it);
        delete emp;
        emp = nullptr;
    }
}

void Manager::removeChatBox(ChatBox* box) {
    auto it = find(chatbox.begin(), chatbox.end(), box);
    if (it != chatbox.end()) {
        chatbox.erase(it);
        delete box;
        box = nullptr;
    }
}