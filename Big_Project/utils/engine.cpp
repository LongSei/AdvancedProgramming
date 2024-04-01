#include "engine.hpp"
using namespace std;

void Game::init(bool IS_FULLSCREEN, int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    isRunning = false;
    int SCREEN_STATUS = IS_FULLSCREEN ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
    // SDL2 Creating
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Image Loader Creating
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }

    // Game Window Creating
    window = SDL_CreateWindow(WINDOW_TITLE,
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_STATUS);
    if (!window) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // Renderer Creating
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    startTime = SDL_GetTicks();
    mainManager.init();
    isRunning = true;
    mainManager.addNewEmployment("ceo", pair<int, int>(0,0), "None", renderer);
}

void Game::handleEvents(SDL_Event event) {
    while (SDL_PollEvent(&event) != 0) {
        cout << SDL_PollEvent(&event) << endl;
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void Game::renderUpdate() {
    mainManager.render(startTime, renderer);
    SDL_RenderPresent(renderer);
}

void Game::renderClear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool Game::running() {
    return isRunning;
}