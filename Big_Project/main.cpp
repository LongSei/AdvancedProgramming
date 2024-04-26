#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "./utils/engine.hpp"
#include "./utils/constant.hpp"
using namespace std;

int main() {
    Game mainGame;
    Characters player = Characters("ceo", {1280, 1280}, "down", PLAYER_SPEED);
    mainGame.init(false, GAME_WIDTH, GAME_HEIGHT, "SeiDev", player);
    mainGame.createMap();
    SDL_Event event;
    mainGame.createEntities(player);

    while (mainGame.running()) {
        mainGame.handleEvents(event);
        mainGame.renderUpdate();
        SDL_Delay(100);
    }
}