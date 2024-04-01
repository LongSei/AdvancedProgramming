#ifndef characters_hpp
#define characters_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

const int breathingAmplitude = 5;
const float breathingSpeed = 3.0f;

class Characters {
    private: 
        string position; 
        pair<int, int> coordinate;
        SDL_Texture* avatar;
        string status;
        set<string> validStatus = {"None", "Talk", "Work"};
        set<string> validPosition = {"ceo", "cpo", "cto", "designer", "hr", "programmer", "reviewer", "tester"};

    public: 
        void init(string position, pair<int, int> coordinate, string status, SDL_Renderer* renderer);
        void render(Uint32 GameStartTime, SDL_Renderer* renderer);
};

#endif