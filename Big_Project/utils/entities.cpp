#include"entities.hpp"

Entities::Entities() {
    name = "NONE";
    max_health = 0;
    health = 0;
    damage = 0;
    speed = 0;
    move_time = 0;
    attack_time = 0;
    coordinate = {0,0};
}

Entities::Entities(string _name, SDL_Point _coordinate) {
    name = _name;
    max_health = ENEMIES_STAT.at(name).at("HEALTH");
    health = max_health;
    damage = ENEMIES_STAT.at(name).at("DAMAGE");
    speed = ENEMIES_STAT.at(name).at("SPEED");
    move_time = ENEMIES_STAT.at(name).at("MOVE TIME");
    attack_time = ENEMIES_STAT.at(name).at("ATTACK TIME");
    coordinate = _coordinate;
    time_wait = SDL_GetTicks();
}

Entities::Entities(const Entities& other) {
    name = other.name;
    max_health = other.max_health;
    health = other.health;
    damage = other.damage;
    speed = other.speed;
    coordinate = other.coordinate;
    time_wait = other.time_wait;
    move_time = other.move_time;
    attack_time = other.attack_time;
}

void Entities::render(SDL_Renderer* renderer, SDL_Point renderPosition) {
    SDL_Rect dstRect = {renderPosition.x, renderPosition.y, TILESIZE, TILESIZE};
    string _image_directory = "";
    auto it = POSSIBLE_MOVES.begin();
    advance(it, status_index);
    string status = *it;
    if (isSendAttack == false) {
        _image_directory = ENEMIES_DIRECTORY + name + "/idle/" + to_string(status_index) + ".png";
    }
    else {
        _image_directory = ENEMIES_DIRECTORY + name + "/attack/0.png";
        isSendAttack = false;
    }
    image = EssentialFunction().loadTexture(_image_directory, renderer);
    SDL_RenderCopy(renderer, image, NULL, &dstRect);

    // Render health bar
    SDL_Rect healthBarRect = {renderPosition.x, renderPosition.y - ENIMIES_MARGIN_WITH_BAR, TILESIZE, ENIMIES_HEALTH_BAR_HEIGHT};
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderDrawRect(renderer, &healthBarRect);

    float ratio = health / max_health; 
    int healthBarWidth = TILESIZE * ratio;
    SDL_Rect currentHealthRect = {renderPosition.x, renderPosition.y - ENIMIES_MARGIN_WITH_BAR, healthBarWidth, ENIMIES_HEALTH_BAR_HEIGHT};
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a); 
    SDL_RenderFillRect(renderer, &currentHealthRect);
}

SDL_Point Entities::getCoordinate() {
    return coordinate;
}

void Entities::send_attack(Characters& player) {
    if (checkCollisionPlayer(player)) {
        player.takeDamage(damage);
    }
}

bool Entities::getCollision(vector<vector<vector<Tile> > >& game_map) {
    SDL_Rect entityRect = {coordinate.x, coordinate.y, TILESIZE, TILESIZE};
    for (int layer = 0; layer <= 2; layer++) {
        for (int y = 0; y < game_map[layer].size(); y++) {
            for (int x = 0; x < game_map[layer][y].size(); x++) {
                Tile& tile = game_map[layer][y][x];
                SDL_Rect tileRect = {x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE};
                if (SDL_HasIntersection(&entityRect, &tileRect) && tile.groupCheck["walkon"] == false) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Entities::send_move(const string& move_way) {
    if (move_way == "up") {
        coordinate.y -= speed;
    }
    else if (move_way == "down") {
        coordinate.y += speed;
    }
    else if (move_way == "left") {
        coordinate.x -= speed;
    }
    else if (move_way == "right") {
        coordinate.x += speed;
    }
}

void Entities::update_move(const string& move_way) {
    SDL_Point previous_move = coordinate;
    if (move_way == "up") {
        previous_move.y += speed;
    }
    else if (move_way == "down") {
        previous_move.y -= speed;
    }
    else if (move_way == "left") {
        previous_move.x += speed;
    }
    else if (move_way == "right") {
        previous_move.x -= speed;
    }

    if (status == move_way) {
        status_index = (status_index + 1) % 4;
    }
    else {
        status = move_way;
        status_index = 0;
    }
}

void Entities::undo_move(const string& move_way) {
    if (move_way == "up") {
        coordinate.y += speed;
    }
    else if (move_way == "down") {
        coordinate.y -= speed;
    }
    else if (move_way == "left") {
        coordinate.x += speed;
    }
    else if (move_way == "right") {
        coordinate.x -= speed;
    }
}

Uint32 Entities::getTime() {
    return time_wait;
}

float Entities::getSpeed() {
    return speed;
}

void Entities::updateTime(Uint32 new_time) {
    time_wait = new_time;
}

bool Entities::checkCollisionPlayer(Characters& player) {
    SDL_Point playerCoordinate = player.getCoordinate();
    SDL_Rect playerRect = { playerCoordinate.x, playerCoordinate.y, TILESIZE, TILESIZE };
    SDL_Rect entityRect = { coordinate.x, coordinate.y, TILESIZE, TILESIZE };

    if (SDL_HasIntersection(&playerRect, &entityRect)) {
        return true;
    }
    return false;
}

bool Entities::getValidMove(vector<vector<vector<Tile> > >& game_map, Characters& player) {        
    bool isok = true;
    if (getCollision(game_map) == true) isok = false;
    if (checkCollisionPlayer(player) == true) isok = false;
    return isok;
}

int Entities::getMoveTime() {
    return move_time;
}

int Entities::getAttackTime() {
    return attack_time;
}

void Entities::takeDamage(float damage) {
    health -= damage;
}

float Entities::getStatus() {
    return float(health);
}

float Entities::getDamage() {
    return damage;
}