#include "engine.hpp"
using namespace std;

Game::Game(){}
Game::~Game(){}

void Game::logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Game::init(bool IS_FULLSCREEN, int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    isRunning = false;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init" << " " << SDL_GetError() << endl;
    }

    int SCREEN_STATUS = IS_FULLSCREEN ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;


    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_STATUS);
    if (window == nullptr) {
        cout << "CreateWindow" << " " << SDL_GetError() << endl;
    }
    else {
        cout << "Creating Window Successfully" << endl;
    }

    int RENDERING_INDEX = -1;
    renderer = SDL_CreateRenderer(window, RENDERING_INDEX, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        cout << "CreateRenderer" << " " << SDL_GetError() << endl;
    }
    else {
        cout << "Creating Renderer Successfully" << endl;
    }
    isRunning = true;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        default:
            break;
    }
}

void Game::update() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, 800/2, 600/2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = 800 - 400;
    filled_rect.y = 600 - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::running() {
    return isRunning;
}