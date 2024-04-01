#include"../company_tools/manager.hpp"
using namespace std;

void EntitiesManager::init() {
    employment.clear();
    chatbox.clear();
}

void EntitiesManager::addNewEmployment(string position, pair<int, int> coordinate, string status, SDL_Renderer* renderer) {
    Characters* newEmploy = new Characters;
    (*newEmploy).init(position, coordinate, status, renderer);
    employment.push_back(newEmploy);
}

void EntitiesManager::addNewChatBox() {
    ChatBox* newChatBox = new ChatBox;
    (*newChatBox).init();
    chatbox.push_back(newChatBox);
}

void EntitiesManager::removeEmployment(Characters* emp) {
    auto it = find(employment.begin(), employment.end(), emp);
    if (it != employment.end()) {
        employment.erase(it);
        delete emp;
        emp = nullptr;
    }
}

void EntitiesManager::removeChatBox(ChatBox* box) {
    auto it = find(chatbox.begin(), chatbox.end(), box);
    if (it != chatbox.end()) {
        chatbox.erase(it);
        delete box;
        box = nullptr;
    }
}

void EntitiesManager::render(Uint32 GameStartTime, SDL_Renderer* renderer) {
    for (auto character : employment) {
        (*character).render(GameStartTime, renderer);
    }
}