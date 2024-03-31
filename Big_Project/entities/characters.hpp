#ifndef characters_hpp
#define characters_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"./company_tools/chatbox.hpp"
using namespace std;

class Characters {
    private: 
        string position; 
        string avatar;

    public: 
        void init(string Position, string avatar_directory);
        void chatMessage(ChatBox* box, string message); 
};

#endif