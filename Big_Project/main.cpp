#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "./utils/engine.hpp"
#include "./utils/constant.hpp"
using namespace std;

int main() {
    Game mainGame;
    Characters player = Characters({1280, 1280}, "down", PLAYER_SPEED);
    mainGame.init(false, GAME_WIDTH, GAME_HEIGHT, "SeiDev", player);
    mainGame.createMap();
    SDL_Event event;
    while (mainGame.running()) {
        SDL_RenderClear(mainGame.renderer);
        mainGame.handleEvents(event);
        Uint32 current_time = SDL_GetTicks() % (ENTITIES_SPAWN_TIME * 1000);
        int lower_bound = ENTITIES_SPAWN_TIME * 1000 - int(ENTITIES_SPAWN_TOLERANCE * 1000);
        int upper_bound = int(ENTITIES_SPAWN_TOLERANCE * 1000);
        if (current_time <= upper_bound || current_time >= lower_bound) {
            mainGame.playerClearEntity();
        }
        if (mainGame.stopping() == false) {
            mainGame.renderUpdate();
            SDL_RenderPresent(mainGame.renderer);
        }
        SDL_Delay(100);

    }
}