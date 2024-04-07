#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "./utils/engine.hpp"
#include "./utils/constant.hpp"
using namespace std;

int main() {
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

// const int WINDOW_WIDTH = 800;
// const int WINDOW_HEIGHT = 600;
// const int BOX_SIZE = 50;

// // Function to initialize SDL and create a window
// SDL_Window* initialize_window() {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("SDL Hitbox Example",
//                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//                                           WINDOW_WIDTH, WINDOW_HEIGHT, 0);
//     return window;
// }

// // Check if two boxes overlap
// bool check_collision(SDL_Rect a, SDL_Rect b) {
//     // Calculate the sides of rect A
//     int leftA = a.x;
//     int rightA = a.x + a.w;
//     int topA = a.y;
//     int bottomA = a.y + a.h;

//     // Calculate the sides of rect B
//     int leftB = b.x;
//     int rightB = b.x + b.w;
//     int topB = b.y;
//     int bottomB = b.y + b.h;

//     // If any of the sides from A are outside of B
//     if (bottomA <= topB) {
//         return false;
//     }
//     if (topA >= bottomB) {
//         return false;
//     }
//     if (rightA <= leftB) {
//         return false;
//     }
//     if (leftA >= rightB) {
//         return false;
//     }

//     // If none of the sides from A are outside B
//     return true;
// }

// int main() {
//     SDL_Window* window = initialize_window();
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     SDL_Rect hitbox = {WINDOW_WIDTH / 2 - BOX_SIZE, WINDOW_HEIGHT / 2 - BOX_SIZE, BOX_SIZE, BOX_SIZE};
//     SDL_Rect movingBox = {0, 0, BOX_SIZE, BOX_SIZE};

//     SDL_Event event;
//     bool running = true;
//     while (running) {
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//             if (event.type == SDL_KEYDOWN) {
//                 switch (event.key.keysym.sym) {
//                     case SDLK_LEFT:
//                         movingBox.x -= 10;
//                         break;
//                     case SDLK_RIGHT:
//                         movingBox.x += 10;
//                         break;
//                     case SDLK_UP:
//                         movingBox.y -= 10;
//                         break;
//                     case SDLK_DOWN:
//                         movingBox.y += 10;
//                         break;
//                 }
//             }
//         }

//         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White background
//         SDL_RenderClear(renderer);

//         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red hitbox
//         SDL_RenderFillRect(renderer, &hitbox);

//         // Change color if collision detected
//         if (check_collision(hitbox, movingBox)) {
//             SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green moving box if colliding
//         } else {
//             SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue moving box if not colliding
//         }
//         SDL_RenderFillRect(renderer, &movingBox);

//         SDL_RenderPresent(renderer);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }
