#include "engine.hpp"
using namespace std;

void Game::init(bool _IS_FULLSCREEN, int _SCREEN_WIDTH, int _SCREEN_HEIGHT, const char* _SCREEN_TITLE, const char* _GAME_MUSIC_PATH, Characters& _mainPlayer) {
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

    // Font Loader Creating
    if (!(TTF_Init() == 0)) {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    music = Mix_LoadMUS(_GAME_MUSIC_PATH);
    if (!music) {
        printf("Failed to load OGG music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
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

    loadSoundEffect();

    IS_FULLSCREEN = _IS_FULLSCREEN;
    SCREEN_HEIGHT = _SCREEN_HEIGHT;
    SCREEN_WIDTH = _SCREEN_WIDTH;
    SCREEN_TITLE = _SCREEN_TITLE;
    ScreenCamera = CameraScreen(renderer);
    mainPlayer = _mainPlayer;
}

void Game::playerClearEntity() {
    if (game_entities.size() == 0) {
        if (amount_entities >= MAX_ENTITIES) {
            isRunning = false;
        }
        for (int amount = 1; amount <= amount_entities; amount++) {
            createEntities();
        }
        amount_entities += EssentialFunction().choice(RANDOM_AMOUNT_ENTITIES);
    }
}

void Game::loadSoundEffect() {
    game_music["GAME_HIT"] = Mix_LoadWAV(GAME_HIT_PATH.c_str());
    game_music["GAME_HEAL"] = Mix_LoadWAV(GAME_HEAL_PATH.c_str());
    game_music["GAME_DEATH"] = Mix_LoadWAV(GAME_DEATH_PATH.c_str());
}

void Game::createEntities() {
    string name_entities = EssentialFunction().choice(ENIMIES_NAME);
    
    SDL_Point playerCoordinate = mainPlayer.getCoordinate();
    SDL_Point enemyCoordinate = playerCoordinate;
    bool isValid = false;
    while (isValid == false) {
        int offsetX = EssentialFunction().randint(RANGE_ENEMY_OFF_SET_X.first, RANGE_ENEMY_OFF_SET_X.second);
        int offsetY = EssentialFunction().randint(RANGE_ENEMY_OFF_SET_Y.first, RANGE_ENEMY_OFF_SET_Y.second);
        while (offsetX == 0 && offsetY == 0) {
            offsetX = EssentialFunction().randint(RANGE_ENEMY_OFF_SET_X.first, RANGE_ENEMY_OFF_SET_X.second);
            offsetY = EssentialFunction().randint(RANGE_ENEMY_OFF_SET_Y.first, RANGE_ENEMY_OFF_SET_Y.second);
        }
        enemyCoordinate = {min(MAP_IMAGE_WIDTH, playerCoordinate.x + offsetX * TILESIZE), min(MAP_IMAGE_HEIGHT, playerCoordinate.y + offsetY * TILESIZE)};
        enemyCoordinate = {max(0, enemyCoordinate.x - (enemyCoordinate.x % TILESIZE)), max(0, enemyCoordinate.y  - (enemyCoordinate.y % TILESIZE))};
        isValid = true;
        for (int layer = 0; layer <= 2; layer++) {
            Tile& tile = game_map[layer][enemyCoordinate.y / TILESIZE][enemyCoordinate.x / TILESIZE];
            if (tile.groupCheck["walkon"] == false) {
                isValid = false;
                break;
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
                        game_map[0][col_index][row_index] = Tile(NULL, groupCheck, x, y);
                    }
                    else if (blockStyle == "map_Grass.csv") {
                        map<string, bool> groupCheck = {{"visible", true}, {"attackable", false}, {"walkon", false}};
                        SDL_Texture* image = EssentialFunction().choice(graphics["grass"]);
                        game_map[1][col_index][row_index] = Tile(image, groupCheck, x, y);
                    }
                    else if (blockStyle == "map_Objects.csv") {
                        map<string, bool> groupCheck = {{"visible", true}, {"attackable", false}, {"walkon", false}};
                        SDL_Texture* image = graphics["objects"][row[0] - '0'];
                        game_map[2][col_index][row_index] = Tile(image, groupCheck, x, y);
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
                    SDL_Rect attackedRect = {attackedTile.x, attackedTile.y, TILESIZE, TILESIZE};
                    for (int enemyIndex = 0; enemyIndex < game_entities.size(); enemyIndex++) {
                        Entities& enemy = game_entities[enemyIndex];
                        SDL_Point enemyCoordinate = enemy.getCoordinate();
                        SDL_Rect enemyRect = {enemyCoordinate.x, enemyCoordinate.y, TILESIZE, TILESIZE};
                        if (SDL_HasIntersection(&attackedRect, &enemyRect)) {
                            enemy.takeDamage(mainPlayer.getDamage());
                            Mix_PlayChannel( -1, game_music["GAME_HIT"], 0 );
                            if (enemy.getStatus() <= 0) {
                                game_entities.erase(game_entities.begin() + enemyIndex);
                                Mix_PlayChannel( -1, game_music["GAME_DEATH"], 0 );
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
                mainPlayer.update_move(move_way);
                return;
            }
        }
    }

    for (int enemyIndex = 0; enemyIndex < game_entities.size(); enemyIndex++) {
        Entities& enemy = game_entities[enemyIndex];
        if (enemy.checkCollisionPlayer(mainPlayer)) {
            mainPlayer.undo_move(move_way);
            mainPlayer.update_move(move_way);
            return;
        }
    }
    mainPlayer.update_move(move_way);
}

void Game::entitiesHandle() {
    for (auto& enemy : game_entities) {
        Uint32 current_time = SDL_GetTicks();

        int remain_move = current_time % int(enemy.getMoveTime() * 1000);
        int lower_bound_move = int(enemy.getMoveTime() * 1000 - TOLERANCE_ENEMY_MOVE * 1000);
        int upper_bound_move = TOLERANCE_ENEMY_MOVE * 1000;

        if (remain_move <= upper_bound_move || remain_move >= lower_bound_move) {
            map<string, bool> check = {{"up", false}, {"down", false}, {"left", false}, {"right", false}};
            int remainCheck = 4;
            string move_way = "up";
            while (remainCheck) {
                while (check[move_way] == true) {
                    move_way = EssentialFunction().choice(POSSIBLE_MOVES);
                    if (check[move_way] == false) {
                        break;
                    }
                }
                remainCheck--;
                check[move_way] = true;
                int OldDistance = abs(enemy.getCoordinate().x - mainPlayer.getCoordinate().x) + abs(enemy.getCoordinate().y - mainPlayer.getCoordinate().y);
                enemy.send_move(move_way);
                int NewDistance = abs(enemy.getCoordinate().x - mainPlayer.getCoordinate().x) + abs(enemy.getCoordinate().y - mainPlayer.getCoordinate().y);
                
                if (enemy.getValidMove(game_map, mainPlayer)) {
                    if (NewDistance < OldDistance) {
                        enemy.update_move(move_way);
                        break;
                    } 
                    else {
                        enemy.undo_move(move_way);
                    }
                } 
                else if (enemy.checkCollisionPlayer(mainPlayer)) {
                    int attack_interval_ms = int(enemy.getAttackTime() * 1000);
                    int tolerance_ms = TOLERANCE_ENEMY_ATTACK * 1000;
                    int remain_attack = current_time % attack_interval_ms;
                    if (remain_attack <= tolerance_ms || (attack_interval_ms - remain_attack) <= tolerance_ms) {
                        enemy.send_attack(mainPlayer);
                        startTime = SDL_GetTicks();
                    }
                    enemy.undo_move(move_way);
                    break;
                } 
                else {
                    enemy.undo_move(move_way);
                }
            }
        }
        ScreenCamera.entitiesDraw(enemy);
    }
}

void Game::renderUpdate() {
    if (mainPlayer.getStatus().first <= 0 || isStopping == true) {
        gameOverScreen();
    }
    else {
        ScreenCamera.calculateVisibleArea(mainPlayer.getCenter());
        ScreenCamera.mapDraw(game_map);
        ScreenCamera.playerDraw(mainPlayer);
        entitiesHandle();
        ScreenCamera.status_bar(mainPlayer, game_music["GAME_HEAL"], startTime);
        ScreenCamera.score_show(mainPlayer);
    }
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
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
    isStopping = true;
    string GAME_OVER_STRING = "GAME OVER\n" + to_string(mainPlayer.getExp());
    SDL_Texture* game_over_background = EssentialFunction().loadTexture(GAME_OVER_IMAGE, renderer);
    SDL_RenderCopy(renderer, game_over_background, NULL, NULL);
    SDL_DestroyTexture(game_over_background);

    TTF_Font* font = TTF_OpenFont(FONT_PATH.c_str(), GAME_OVER_FONT_SIZE);
    int line_height = TTF_FontLineSkip(font);
    vector<string> lineText = EssentialFunction().split(GAME_OVER_STRING, '\n');
    int currentLineIdx = 0;
    int amountLines = lineText.size();
    int totalY = 0;

    while (currentLineIdx != amountLines) {
        string text = lineText[currentLineIdx];
        SDL_Texture* texture = EssentialFunction().loadFont(font, GAME_OVER_FONT_SIZE, GAME_OVER_FONT_COLOR, text, renderer);
        int texture_width, texture_height;
        SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
        if (currentLineIdx == 0) {
            totalY = texture_height * amountLines + GAME_OVER_MARGIN * (amountLines - 1);
        }
        SDL_Rect text_rect = { (SCREEN_WIDTH - texture_width) / 2, (SCREEN_HEIGHT - totalY) / 2 + currentLineIdx * (texture_height + GAME_OVER_MARGIN), texture_width, texture_height };
        SDL_RenderCopy(renderer, texture, NULL, &text_rect);
        SDL_DestroyTexture(texture);
        currentLineIdx++;
    }

    TTF_CloseFont(font);
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

void CameraScreen::status_bar(Characters& player, Mix_Chunk* heal_sound, Uint32 startTime) {
    pair<float, float> currentStatus = player.getStatus();
    float currentHealth = currentStatus.first;
    float currentEnergy = currentStatus.second;

    pair<float, float> maxStatus = player.getMaxStatus();
    float maxHealth = maxStatus.first;
    float maxEnergy = maxStatus.second;

    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - startTime;
    if ((elapsedTime % expectedTime <= tolerance) || (elapsedTime % expectedTime >= (expectedTime - tolerance))){
        pair<float, float> prev_status = player.getStatus();
        player.updateStatus();
        pair<float, float> new_status = player.getStatus();
        if (prev_status.first != new_status.first && prev_status.second != new_status.second && new_status.first == maxHealth && new_status.second == maxEnergy) {
            Mix_PlayChannel( -1, heal_sound, 0 );
        }
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
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
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

void CameraScreen::score_show(Characters& player) {
    int score = player.getExp();
    string SCORE_TEXT = "SCORE:" + to_string(score);
    TTF_Font* font = TTF_OpenFont(FONT_PATH.c_str(), SCORE_FONT_SIZE);
    SDL_Texture* texture = EssentialFunction().loadFont(font, SCORE_FONT_SIZE, SCORE_FONT_COLOR, SCORE_TEXT, renderer);
    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

    SDL_Rect textRect = {GAME_WIDTH - text_width - SCORE_MARGIN, SCORE_MARGIN, text_width, text_height};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture); 
    TTF_CloseFont(font); 
}