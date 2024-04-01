#include"./utils/engine.hpp"

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

using namespace std;

bool IS_FULLSCREEN = false;
float WINDOW_WIDTH = 800;
float WINDOW_HEIGHT = 800;
string WINDOW_TITLE = "SeiDev";
bool running = true;

int main(int argc, char* argv[]) {
    Game mainGame;
    mainGame.init(IS_FULLSCREEN, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str());
    SDL_Event event;
    while (mainGame.running()) {
        mainGame.handleEvents(event);
        mainGame.renderClear();
        mainGame.renderUpdate();
    }
}