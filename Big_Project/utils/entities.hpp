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

        string name;
        float max_health;
        float health;
        float damage;
        int speed;
        int move_time;
        int attack_time;

        bool isSendAttack = false;

        SDL_Point coordinate; 

    public: 
        Uint32 time_wait = 0;
        Entities();
        Entities(string name, SDL_Point _coordinate);
        Entities(const Entities& other);
        void render(SDL_Renderer* renderer, SDL_Point renderPosition);
        SDL_Point getCoordinate(); 
        bool getCollision(vector<vector<vector<Tile> > >& game_map);
        Uint32 getTime();
        int getMoveTime();
        int getAttackTime();
        void updateTime(Uint32 new_time);
        float getSpeed();
        float getStatus();
        float getDamage();
        bool getValidMove(vector<vector<vector<Tile> > >& game_map, Characters& player);

        void send_move(const string& move_way);
        void update_move(const string& move_way);
        void undo_move(const string& move_way);
        void send_attack(Characters& player);

        bool checkCollisionPlayer(Characters& player);

        void takeDamage(float damage);
};
#endif
