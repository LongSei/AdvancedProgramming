#include "engine.hpp"
using namespace std;

void Game::init(bool _IS_FULLSCREEN, int _SCREEN_WIDTH, int _SCREEN_HEIGHT, const char* _SCREEN_TITLE) {
    isRunning = false;
    int SCREEN_STATUS = _IS_FULLSCREEN ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
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
    window = SDL_CreateWindow(_SCREEN_TITLE,
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          _SCREEN_WIDTH, _SCREEN_HEIGHT, SCREEN_STATUS);
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
    mainManager.init();
    isRunning = true;
    game_map.resize(3, map<int, map<int, Tile>>());
    IS_FULLSCREEN = _IS_FULLSCREEN;
    SCREEN_HEIGHT = _SCREEN_HEIGHT;
    SCREEN_WIDTH = _SCREEN_WIDTH;
    SCREEN_TITLE = _SCREEN_TITLE;
    ScreenCamera = CameraScreen(renderer);
    mainPlayer = Characters(player_directory,"ceo", {0,0}, "down", renderer);
}

void Game::createMap() {

    map<string, vector<vector<string> > > layouts; 
    map<string, vector<SDL_Texture*> > graphics; 

    // LOAD RESOURCES 
    for (auto directory : list_layouts) {
        vector<vector<string>> csv_file = EssentialFunction().read_csv(directory);
        string file_name = EssentialFunction().split(directory, '/').back();
        layouts[file_name] = csv_file;
    }

    for (auto directory : list_graphics) {
        vector<SDL_Texture*> graphic_objects = EssentialFunction().read_image_folder(directory, renderer);
        string folder_name = EssentialFunction().split(directory, '/').back();
        graphics[folder_name] = graphic_objects;
    }

    // Create Game_Map 
    for (const auto& [blockStyle, layout] : layouts) {
        for (int row_index = 0; row_index < layout.size(); ++row_index) {
            const auto& row = layout[row_index];
            for (int col_index = 0; col_index < row.size(); ++col_index) {
                const auto& col = row[col_index];
                if (col != "-1") {
                    int x = col_index * TILESIZE;
                    int y = row_index * TILESIZE;
                    if (blockStyle == "map_FloorBlocks.csv") {
                        Tile hitbox(NULL, "boundary", false, x, y);
                        game_map[0][row_index][col_index] = hitbox;
                    }
                    else if (blockStyle == "map_Grass.csv") {
                        SDL_Texture* image = EssentialFunction().choice(graphics["grass"]);
                        Tile hitbox(image, "grass", true, x, y);
                        game_map[1][row_index][col_index] = hitbox;
                    }
                    else if (blockStyle == "map_Objects.csv") {
                        SDL_Texture* image = EssentialFunction().choice(graphics["objects"]);
                        Tile hitbox(image, "objects", true, x, y);
                        game_map[2][row_index][col_index] = hitbox;
                    }
                }
            }
        }
    }
}

void Game::handleEvents(SDL_Event event) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    mainPlayer.coordinate.x -= 64;
                    break;
                case SDLK_RIGHT:
                    mainPlayer.coordinate.x += 64;
                    break;
                case SDLK_UP:
                    mainPlayer.coordinate.y -= 64;
                    break;
                case SDLK_DOWN:
                    mainPlayer.coordinate.y += 64;
                    break;
            }
        }
    }
}

void Game::renderUpdate() {
    ScreenCamera.customDraw(mainPlayer, game_map);
    // mainManager.render(startTime, renderer);
    SDL_RenderPresent(renderer);
}

void Game::renderClear() {
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


CameraScreen::CameraScreen() {
    renderer = nullptr; 
    floor_surf = nullptr;
}

CameraScreen::CameraScreen(SDL_Renderer* _renderer) {
    floor_surf = EssentialFunction().loadTexture(backgroundMap, _renderer);
    SDL_Rect screenSize;
    SDL_GetRendererOutputSize(_renderer, &screenSize.w, &screenSize.h);
    half_screen = {screenSize.w / 2, screenSize.h / 2};
    renderer = _renderer;
}

void CameraScreen::calculateVisibleArea(const SDL_Point& center) {
    floor_rect = {max(0, center.x - half_screen.x), max(0, center.y - half_screen.y), half_screen.x * 2, half_screen.y * 2};
}

void CameraScreen::customDraw(Characters& player, vector<map<int, map<int, Tile>>>& game_map) {
    SDL_Point playerCenter = player.getCenter();
    calculateVisibleArea(playerCenter);
    SDL_RenderCopy(renderer, floor_surf, &floor_rect, NULL);
    player.render(renderer, half_screen);

    for (int layer = 0; layer <= 2; layer++) {
        for (int row = max(0, floor_rect.y / TILESIZE); row <= min((floor_rect.y + floor_rect.h) / TILESIZE, static_cast<int>(game_map[layer].size()) - 1); row++) {
            for (int col = max(0, floor_rect.x / TILESIZE); col <= min((floor_rect.x + floor_rect.w) / TILESIZE, static_cast<int>(game_map[layer][row].size()) - 1); col++) {
                Tile& tile = game_map[layer][row][col];
                if (tile.isShown == true) {
                    SDL_Rect tileDest = {col * TILESIZE - floor_rect.x, row * TILESIZE - floor_rect.y, TILESIZE, TILESIZE};
                    if (tileDest.x + TILESIZE > 0 && tileDest.x < floor_rect.w &&
                        tileDest.y + TILESIZE > 0 && tileDest.y < floor_rect.h) {
                        SDL_RenderCopy(renderer, tile.image, NULL, &tileDest);
                    }
                }
            }
        }
    }
}

