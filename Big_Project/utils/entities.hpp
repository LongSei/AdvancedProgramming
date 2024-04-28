#ifndef entities_hpp
#define entities_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"constant.hpp"
#include"essential.hpp"
#include"characters.hpp"
#include"grid.hpp"
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
        int move_time;

        bool isSendAttack = false;

        SDL_Point coordinate; 

    public: 
        Uint32 time_wait = 0;
        Entities();
        Entities(string name, SDL_Point _coordinate);
        Entities(const Entities& other);
        void render(SDL_Renderer* renderer, SDL_Point renderPosition);
        SDL_Point getCoordinate(); 
        vector<SDL_Point> getCollision();
        Uint32 getTime();
        int getMoveTime();
        void updateTime(Uint32 new_time);
        float getSpeed();
        float getStatus();
        float getDamage();
        vector<string> getValidMove(vector<vector<vector<Tile> > >& game_map);

        void send_move(const string& move_way);
        void update_move(const string& move_way);
        void undo_move(const string& move_way);
        SDL_Point send_attack(Characters& player);

        void takeDamage(float damage);
};
#endif
