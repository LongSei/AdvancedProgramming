#ifndef characters_hpp
#define characters_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

const int breathingAmplitude = 5;
const float breathingSpeed = 3.0f;
const int CharacterWidth = 80;
const int CharacterHeight = 100; 

class Characters {
    private: 
        int speed;
        string position; 
        string status;
        SDL_Texture* image;
        set<string> validStatus = {"down", "up", "left", "right"};
        set<string> validPosition = {"ceo", "cpo", "cto", "designer", "hr", "programmer", "reviewer", "tester"};

    public: 
        SDL_Point coordinate;
        Characters();
        Characters(string _image_directory, string _position, SDL_Point _coordinate, string _status, int _speed, SDL_Renderer* _renderer);
        void render(SDL_Renderer* renderer, SDL_Point renderPosition);
        SDL_Point getCoordinate();
        SDL_Point getCenter();
        vector<SDL_Point> getCollision(); 
        void move(const string& move_way);
        
};

#endif