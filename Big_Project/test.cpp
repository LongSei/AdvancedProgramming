#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return texture;
}

SDL_Texture* loadTexturePart(SDL_Renderer* renderer, const std::string& filePath, int x, int y, int xradius, int yradius) {
    // Load the entire texture
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Create a rectangle to define the portion of the texture to extract
    SDL_Rect clipRect = {x - xradius, y - yradius, xradius * 2, yradius * 2};

    // Extract the desired portion of the surface
    SDL_Surface* partSurface = SDL_CreateRGBSurface(0, xradius * 2, yradius * 2, 
                                                    surface->format->BitsPerPixel,
                                                    surface->format->Rmask, 
                                                    surface->format->Gmask,
                                                    surface->format->Bmask, 
                                                    surface->format->Amask);
    if (!partSurface) {
        std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return nullptr;
    }
    SDL_BlitSurface(surface, &clipRect, partSurface, nullptr);

    // Create texture from the extracted surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, partSurface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(partSurface);
        SDL_FreeSurface(surface);
        return nullptr;
    }

    // Clean up
    SDL_FreeSurface(partSurface);
    SDL_FreeSurface(surface);

    return texture;
}


void renderLight(SDL_Renderer* renderer, SDL_Texture* lightTexture, SDL_Texture* backgroundTexture, int x, int y, int xradius, int yradius) {
    // Clear the renderer with a transparent color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Set blend mode to multiply to darken the background
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Darken the background

    // Create a rectangle to represent the area of darkness
    SDL_Rect darkRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // Fill the entire screen with a semi-transparent black color
    SDL_RenderFillRect(renderer, &darkRect);

    // Render the background image
    SDL_Rect backgroundRect = { x - xradius, y - yradius, xradius * 2, yradius * 2 };
    SDL_RenderCopy(renderer, loadTexturePart(renderer, "./images/map.png", x, y, xradius, yradius), nullptr, &backgroundRect);

    // // Set blend mode to add for light effect
    SDL_SetTextureBlendMode(lightTexture, SDL_BLENDMODE_ADD);

    // // Render the light texture within the specified circle
    SDL_Rect lightRect = { x - xradius, y - yradius, 2 * xradius, 2 * yradius };
    SDL_RenderCopy(renderer, lightTexture, nullptr, &lightRect);

    // Present the renderer
    SDL_RenderPresent(renderer);
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Lighting and Shadow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* backgroundTexture = loadTexture(renderer, "./images/map.png");
    if (!backgroundTexture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Load light texture
    SDL_Texture* lightTexture = loadTexture(renderer, "./images/light.png");
    if (!lightTexture) {
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Get mouse coordinates
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render light at mouse position
        renderLight(renderer, lightTexture, backgroundTexture, mouseX, mouseY, 100, 75);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(lightTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
