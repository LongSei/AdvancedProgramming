#ifndef characters_hpp
#define characters_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"constant.hpp"
#include"essential.hpp"
using namespace std;

const int breathingAmplitude = 5;
const float breathingSpeed = 3.0f;
const int CharacterWidth = 80;
const int CharacterHeight = 100; 

class Characters {
    private: 
        int speed;
        SDL_Point coordinate;
        string status;
        int status_index = 0;

        SDL_Texture* image;
        set<string> validStatus = {"down", "up", "left", "right"};
        
        float maxHealth = PLAYER_HEALTH;
        float maxEnergy = PLAYER_ENERGY;
        float health = maxHealth;
        float energy = maxEnergy;
        float accHealth = HEALTH_ACCELERATE;
        float accEnergy = ENERGY_ACCELERATE;

        int health_time_refill = 0;
        int energy_time_refill = 0;

        bool isHealthDecrease = false;
        bool isEnergyDecrease = false;

        bool isSendAttack = false;

        float damage = 10;
        int experiance = 0;

    public: 
        Characters();
        Characters(SDL_Point _coordinate, string _status, int _speed);
        void render(SDL_Renderer* renderer, SDL_Point renderPosition);

        SDL_Point getCoordinate();
        SDL_Point getCenter();
        vector<SDL_Point> getCollision(); 
        pair<float, float> getAccelerate();
        pair<float, float> getStatus();
        pair<float, float> getMaxStatus();
        float getDamage();
        int getExp();

        void updateStatus();
        void send_move(const string& move_way);
        void update_move(const string& move_way);
        void undo_move(const string& move_way);
        SDL_Point send_attack();

        void takeDamage(float damage);
        void takeExp();
};

#endif