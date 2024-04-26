#ifndef entities_hpp
#define entities_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"constant.hpp"
#include"essential.hpp"
#include"characters.hpp"
using namespace std;

class Entities {
    private: 
        string position; 
        int status_index = 0;
        string status;

        SDL_Texture* image;
        set<string> validStatus = {"down", "up", "left", "right"};

        string name;
        float health;
        float damage;
        float speed;

        bool isSendAttack = false;

        SDL_Point coordinate; 

    public: 
        Entities();
        Entities(string name, SDL_Point _coordinate);
        void render(SDL_Renderer* renderer, SDL_Point renderPosition);
        SDL_Point getCoordinate(); 

        void send_move(const string& move_way);
        SDL_Point send_attack(Characters& player);
};
#endif
