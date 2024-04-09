#include"../company_tools/manager.hpp"
#include"../constant.hpp"
using namespace std;

void EntitiesManager::init() {
    employment.clear();
    chatbox.clear();
}

void EntitiesManager::addNewEmployment(string image_directory, string position, SDL_Point coordinate, string status, SDL_Renderer* renderer) {
    Characters* newEmploy = new Characters;
    (*newEmploy) = Characters(image_directory, position,  coordinate,  status, PLAYER_SPEED, renderer);
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

void EntitiesManager::render(SDL_Renderer* renderer, SDL_Point renderPosition) {
    for (auto character : employment) {
        (*character).render(renderer, renderPosition);
    }
}