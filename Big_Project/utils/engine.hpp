#ifndef engine_hpp
#define engine_hpp

#include "SDL.h"
#include <iostream>

class Game {
    public:
        Game();
        ~Game();

        void init(bool fullscreen, int width, int height, const char* title);

        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();
        void logErrorAndExit(const char* msg, const char* error);

    private: 
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif