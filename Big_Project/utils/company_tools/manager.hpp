#ifndef manager_hpp
#define manager_hpp
#include<bits/stdc++.h>
#include"../company_tools/chatbox.hpp"
using namespace std;

class EntitiesManager {
    public:
        void init();
        void addNewEmployment(string image_directory, string position, SDL_Point coordinate, string status, SDL_Renderer* renderer);
        void addNewChatBox();
        void removeEmployment(Characters* emploment);
        void removeChatBox(ChatBox* chatbox);
        void render(SDL_Renderer* renderer, SDL_Point renderPosition);

    private: 
        vector<Characters*> employment;
        vector<ChatBox*> chatbox;
};

#endif