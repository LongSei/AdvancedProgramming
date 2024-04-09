#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "./utils/engine.hpp"
#include "./utils/constant.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    Game mainGame;
    mainGame.init(false, GAME_WIDTH, GAME_HEIGHT, "SeiDev");
    mainGame.createMap();
    SDL_Event event;
    while (mainGame.running()) {
        mainGame.handleEvents(event);
        mainGame.renderClear();
        mainGame.renderUpdate();
    }
}