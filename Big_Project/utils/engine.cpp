#include "engine.hpp"
using namespace std;

void Game::init(bool _IS_FULLSCREEN, int _SCREEN_WIDTH, int _SCREEN_HEIGHT, const char* _SCREEN_TITLE, Characters& _mainPlayer) {
    isRunning = false;
    isStopping = false;
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
    isRunning = true;

    vector<int> game_map_sizes = {3, MAP_IMAGE_HEIGHT / TILESIZE, MAP_IMAGE_WIDTH / TILESIZE};
    game_map.resize(game_map_sizes[0]);  // Resize the number of layers
    for (auto& layer : game_map) {
        layer.resize(game_map_sizes[1]);  // Resize the number of rows in each layer
        for (auto& row : layer) {
            row.resize(game_map_sizes[2], Tile());  // Resize the number of columns in each row, initialize with default_value
        }
    }

    IS_FULLSCREEN = _IS_FULLSCREEN;
    SCREEN_HEIGHT = _SCREEN_HEIGHT;
    SCREEN_WIDTH = _SCREEN_WIDTH;
    SCREEN_TITLE = _SCREEN_TITLE;
    ScreenCamera = CameraScreen(renderer);
    mainPlayer = _mainPlayer;
}

void Game::createEntities() {
    string name_entities = EssentialFunction().choice(ENIMIES_NAME);
    
    SDL_Point playerCoordinate = mainPlayer.getCoordinate();
    SDL_Point enemyCoordinate = playerCoordinate;
    bool isValid = false;
    while (isValid == false) {
        int offsetX = EssentialFunction().randint(RANGE_ENEMY_OFF_SET_X.first, RANGE_ENEMY_OFF_SET_X.second);
        int offsetY = EssentialFunction().randint(RANGE_ENEMY_OFF_SET_Y.first, RANGE_ENEMY_OFF_SET_Y.second);
        enemyCoordinate = {min(MAP_IMAGE_WIDTH, playerCoordinate.x + offsetX * TILESIZE), min(MAP_IMAGE_HEIGHT, playerCoordinate.y + offsetY * TILESIZE)};
        isValid = true;
        for (int layer = 0; layer < 3; layer++) {
            if (game_map[layer][enemyCoordinate.y / TILESIZE][enemyCoordinate.x / TILESIZE].groupCheck["walkon"] == false) {
                isValid = false;
            }
        }
    }
    Entities enemy(name_entities, enemyCoordinate);
    game_entities.push_back(enemy);
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
            SDL_Point pre_position = mainPlayer.getCoordinate();
            switch (event.key.keysym.sym) {
                case SDLK_a:
                    mainPlayer.send_move("left");
                    playerHandle("left");
                    break;
                case SDLK_d:
                    mainPlayer.send_move("right");
                    playerHandle("right");
                    break;
                case SDLK_w:
                    mainPlayer.send_move("up");
                    playerHandle("up");
                    break;
                case SDLK_s:
                    mainPlayer.send_move("down");
                    playerHandle("down");
                    break;
                case SDLK_j:
                    SDL_Point attackedTile = mainPlayer.send_attack();
                    for (int enemyIndex = 0; enemyIndex < game_entities.size(); enemyIndex++) {
                        Entities& enemy = game_entities[enemyIndex];
                        SDL_Point enemyCoordinate = enemy.getCoordinate();
                        if (enemyCoordinate.x == attackedTile.x && enemyCoordinate.y == attackedTile.y) {
                            enemy.takeDamage(mainPlayer.getDamage());
                            if (enemy.getStatus() <= 0) {
                                game_entities.erase(game_entities.begin() + enemyIndex);
                                mainPlayer.takeExp();
                            }
                        }
                    }
            }
        }
    }
}

void Game::playerHandle(const string& move_way) {
    vector<SDL_Point> collision = mainPlayer.getCollision();
    for (SDL_Point& collisionCoordinate : collision) {
        for (int layer = 0; layer <= 2; layer++) {
            Tile& tile = game_map[layer][collisionCoordinate.y / TILESIZE][collisionCoordinate.x / TILESIZE];
            if (tile.groupCheck["walkon"] == false) {
                mainPlayer.undo_move(move_way);
                return;
            }
        }
    }
    mainPlayer.update_move(move_way);
}

void Game::entitiesHandle() {
    for (auto& enemy : game_entities) {
        Uint32 current_time = SDL_GetTicks();

        int remain = current_time % int(enemy.getMoveTime() * 1000);
        int lower_bound = int(enemy.getMoveTime() * 1000 - TOLERANCE_ENEMY_MOVE * 1000);
        int upper_bound = TOLERANCE_ENEMY_MOVE * 1000;

        if ((remain <= upper_bound) || (remain >= lower_bound)) {
            vector<string> validMove = enemy.getValidMove(game_map);
            string move_way = EssentialFunction().choice(validMove);

            SDL_Point playerCoordinate = mainPlayer.getCoordinate();
            SDL_Point oldEnemyCoordinate = enemy.getCoordinate();

            int oldDistance = fabs(playerCoordinate.x - oldEnemyCoordinate.x) + fabs(playerCoordinate.y - oldEnemyCoordinate.y);
            
            enemy.send_move(move_way);
            SDL_Point newEnemyCoordinate = enemy.getCoordinate();
            int newDistance = fabs(playerCoordinate.x - newEnemyCoordinate.x) + fabs(playerCoordinate.y - newEnemyCoordinate.y);
            if (newDistance == 0) {
                mainPlayer.takeDamage(enemy.getDamage());
                if (mainPlayer.getStatus().first <= 0) {
                    gameOverScreen();
                    return;
                }
            }
            if (newDistance > oldDistance || newDistance == 0) {
                enemy.undo_move(move_way);
            }
            else {
                enemy.update_move(move_way);
            }
        }
        ScreenCamera.entitiesDraw(enemy);
    }
}

void Game::renderUpdate() {
    ScreenCamera.calculateVisibleArea(mainPlayer.getCenter());
    ScreenCamera.mapDraw(game_map);
    ScreenCamera.playerDraw(mainPlayer);
    ScreenCamera.status_bar(mainPlayer, startTime);
    entitiesHandle();
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

bool Game::stopping() {
    return isStopping;
}

void Game::gameOverScreen() {
    SDL_RenderClear(renderer);
    isStopping = true;
    SDL_Texture* game_over = EssentialFunction().loadTexture(ASSET_DIRECTORY + "game_over.png", renderer);
    SDL_RenderCopy(renderer, game_over, NULL, NULL);
}

CameraScreen::CameraScreen() {
    renderer = nullptr; 
    floor_surf = nullptr;
}

CameraScreen::CameraScreen(SDL_Renderer* _renderer) {
    floor_surf = EssentialFunction().loadTexture(backgroundMap, _renderer);
    SDL_QueryTexture(floor_surf, NULL, NULL, &MAP_WIDTH, &MAP_HEIGHT);
    SDL_Rect screenSize;
    SDL_GetRendererOutputSize(_renderer, &screenSize.w, &screenSize.h);
    half_screen = {screenSize.w / 2, screenSize.h / 2};
    renderer = _renderer;
}

void CameraScreen::calculateVisibleArea(const SDL_Point& center) {
    floor_rect = {max(0, min(MAP_WIDTH - half_screen.x * 2, center.x - half_screen.x)), max(0, min(MAP_HEIGHT - half_screen.y * 2, center.y - half_screen.y)), half_screen.x * 2, half_screen.y * 2};
}

void CameraScreen::status_bar(Characters& player, Uint32 startTime) {
    pair<float, float> currentStatus = player.getStatus();
    float currentHealth = currentStatus.first;
    float currentEnergy = currentStatus.second;

    pair<float, float> maxStatus = player.getMaxStatus();
    float maxHealth = maxStatus.first;
    float maxEnergy = maxStatus.second;

    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - startTime;
    if ((elapsedTime % expectedTime <= tolerance) || (elapsedTime % expectedTime >= (expectedTime - tolerance))){
        player.updateStatus();
    }
    // DETAIL
    float ratio = currentHealth / maxHealth;
    int current_width = (int)(HEALTH_BAR.w * ratio);
    SDL_Rect current_rect = HEALTH_BAR;
    current_rect.w = current_width;
    SDL_SetRenderDrawColor(renderer, HEALTH_COLOR.r, HEALTH_COLOR.g, HEALTH_COLOR.b, HEALTH_COLOR.a);
    SDL_RenderFillRect(renderer, &current_rect);

    ratio = currentEnergy / maxEnergy;
    current_width = (int)(ENERGY_BAR.w * ratio);
    current_rect = ENERGY_BAR;
    current_rect.w = current_width;
    SDL_SetRenderDrawColor(renderer, ENERGY_COLOR.r, ENERGY_COLOR.g, ENERGY_COLOR.b, ENERGY_COLOR.a);
    SDL_RenderFillRect(renderer, &current_rect);

    // BORDER
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &ENERGY_BAR);
    SDL_RenderDrawRect(renderer, &HEALTH_BAR);
}

void CameraScreen::mapDraw(vector<vector<vector<Tile> > >& game_map) {
    SDL_RenderCopy(renderer, floor_surf, &floor_rect, NULL);

    for (int layer = 0; layer <= 2; layer++) {
        for (auto& rowValue : game_map[layer]) {
            for (auto& colValue : rowValue) {
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

void CameraScreen::playerDraw(Characters& player) {
    SDL_Point playerCoordinate = player.getCoordinate();
    player.render(renderer, {playerCoordinate.x - floor_rect.x, playerCoordinate.y - floor_rect.y});
}

void CameraScreen::entitiesDraw(Entities& enemy) {
    SDL_Point enemyCoordinate = enemy.getCoordinate();
    SDL_Point tileDest = {enemyCoordinate.x - floor_rect.x, enemyCoordinate.y - floor_rect.y};
    if (tileDest.x >= 0 && tileDest.x <= floor_rect.w &&
        tileDest.y >= 0 && tileDest.y <= floor_rect.h) {
        enemy.render(renderer, tileDest);       
    }
}