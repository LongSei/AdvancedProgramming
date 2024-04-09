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
    mainPlayer = Characters(PLAYER_DIRECTORY,"ceo", PLAYER_SPAWNER, "down", PLAYER_SPEED, renderer);
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
        for (int col_index = 0; col_index < layout.size(); ++col_index) {
            const auto& col = layout[col_index];
            for (int row_index = 0; row_index < col.size(); ++row_index) {
                const auto& row = col[row_index];
                if (row != "-1") {
                    int x = col_index * TILESIZE;
                    int y = row_index * TILESIZE;
                    if (blockStyle == "map_FloorBlocks.csv") {
                        map<string, bool> groupCheck = {{"visible", false}, {"attackable", false}, {"walkon", false}};
                        Tile hitbox = Tile(NULL, groupCheck, x, y);
                        game_map[0][col_index][row_index] = hitbox;
                    }
                    else if (blockStyle == "map_Grass.csv") {
                        map<string, bool> groupCheck = {{"visible", true}, {"attackable", false}, {"walkon", false}};
                        SDL_Texture* image = EssentialFunction().choice(graphics["grass"]);
                        Tile hitbox = Tile(image, groupCheck, x, y);
                        game_map[1][col_index][row_index] = hitbox;
                    }
                    else if (blockStyle == "map_Objects.csv") {
                        map<string, bool> groupCheck = {{"visible", true}, {"attackable", false}, {"walkon", false}};
                        SDL_Texture* image = graphics["objects"][row[0] - '0'];
                        Tile hitbox = Tile(image, groupCheck, x, y);
                        game_map[2][col_index][row_index] = hitbox;
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
            SDL_Point pre_position = mainPlayer.coordinate;
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    mainPlayer.move("left");
                    break;
                case SDLK_RIGHT:
                    mainPlayer.move("right");
                    break;
                case SDLK_UP:
                    mainPlayer.move("up");
                    break;
                case SDLK_DOWN:
                    mainPlayer.move("down");
                    break;
            }
            vector<SDL_Point> collision = mainPlayer.getCollision();
            for (SDL_Point& collisionCoordinate : collision) {
                for (int layer = 0; layer <= 2; layer++) {
                    Tile& tile = game_map[layer][collisionCoordinate.y / TILESIZE][collisionCoordinate.x / TILESIZE];
                    if (tile.groupCheck["walkon"] == false) {
                        mainPlayer.coordinate = pre_position;
                        return;
                    }
                }
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
    player.render(renderer, {player.coordinate.x - floor_rect.x, player.coordinate.y - floor_rect.y});

    for (int layer = 0; layer <= 2; layer++) {
        for (auto& [rowIndex, rowValue] : game_map[layer]) {
            for (auto& [colIndex, colValue] : rowValue) {
                Tile& tile = colValue; 
                int& row = tile.box.posX;
                int& col = tile.box.posY;
                
                bool& visible = tile.groupCheck["visible"];
                bool& walkon = tile.groupCheck["walkon"];
                bool& attackable = tile.groupCheck["attackable"];

                SDL_Rect tileDest = {col - floor_rect.x, row - floor_rect.y, TILESIZE, TILESIZE};

                if (visible == true) {
                    if (tileDest.x >= 0 && tileDest.x <= floor_rect.w &&
                        tileDest.y >= 0 && tileDest.y <= floor_rect.h) {
                        SDL_RenderCopy(renderer, tile.image, NULL, &tileDest);
                    }
                }
            }
        }
    }
}

