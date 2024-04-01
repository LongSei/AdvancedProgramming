#ifndef engine_hpp
#define engine_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"../entities/characters.hpp"
#include"../company_tools/chatbox.hpp"
#include"../company_tools/manager.hpp"

class Game {
    public:
        void init(bool fullscreen, int width, int height, const char* title);
        void handleEvents(SDL_Event event);
        void renderUpdate();
        void renderClear();
        void clean();
        bool running();
    private: 
        bool isRunning;
        Uint32 startTime;
        SDL_Window* window;
        SDL_Renderer* renderer;
        EntitiesManager mainManager;
};

#endif