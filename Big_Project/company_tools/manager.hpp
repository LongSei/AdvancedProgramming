#ifndef manager_hpp
#define manager_hpp
#include<bits/stdc++.h>
#include"../company_tools/chatbox.hpp"
#include"../entities/characters.hpp"
using namespace std;

class EntitiesManager {
    public:
        void init();
        void addNewEmployment(string position, pair<int, int> coordinate, string status, SDL_Renderer* renderer);
        void addNewChatBox();
        void removeEmployment(Characters* emploment);
        void removeChatBox(ChatBox* chatbox);
        void render(Uint32 GameStartTime, SDL_Renderer* renderer);

    private: 
        vector<Characters*> employment;
        vector<ChatBox*> chatbox;
};

#endif