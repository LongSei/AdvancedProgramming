#include"entities.hpp"

Entities::Entities() {
    name = "NONE";
    health = 0;
    damage = 0;
    speed = 0;
    coordinate = {0,0};
}

Entities::Entities(string _name, SDL_Point _coordinate) {
    name = _name;
    health = ENEMIES_STAT.at(name).at("HEALTH");
    damage = ENEMIES_STAT.at(name).at("DAMAGE");
    speed = ENEMIES_STAT.at(name).at("SPEED");
    move_time = ENEMIES_STAT.at(name).at("MOVE TIME");
    coordinate = _coordinate;
    time_wait = SDL_GetTicks();
}

Entities::Entities(const Entities& other) {
    name = other.name;
    health = other.health;
    damage = other.damage;
    speed = other.speed;
    coordinate = other.coordinate;
    time_wait = other.time_wait;
    move_time = other.move_time;
}

void Entities::render(SDL_Renderer* renderer, SDL_Point renderPosition) {
    SDL_Rect dstRect = {renderPosition.x, renderPosition.y, TILESIZE, TILESIZE};
    string _image_directory = "";
    auto it = validStatus.begin();
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
}

SDL_Point Entities::getCoordinate() {
    return coordinate;
}

SDL_Point Entities::send_attack(Characters& player) {
    SDL_Point attack_coordinate = coordinate;
    if (status == "up") {
        coordinate.y -= speed;
    }
    else if (status == "down") {
        coordinate.y += speed;
    }
    else if (status == "left") {
        coordinate.x -= speed;
    }
    else if (status == "right") {
        coordinate.x += speed;
    }
    SDL_Point playerCoordinate = player.getCoordinate();
    if (playerCoordinate.x == attack_coordinate.x && playerCoordinate.y == attack_coordinate.y) {
        isSendAttack = true;
        return attack_coordinate;
    }
    return {0,0};
}

vector<SDL_Point> Entities::getCollision() {
    int& posX = coordinate.x;
    int& posY = coordinate.y;
    vector<SDL_Point> collisionBlock;
    if (posX % TILESIZE != 0 && posY % TILESIZE != 0) {
        collisionBlock.push_back({posX - (posX % TILESIZE), posY - (posY % TILESIZE)});
        collisionBlock.push_back({posX - (posX % TILESIZE), posY + (TILESIZE - (posY % TILESIZE))});
        collisionBlock.push_back({posX + (TILESIZE - (posX % TILESIZE)), posY - (posY % TILESIZE)});
        collisionBlock.push_back({posX + (TILESIZE - (posX % TILESIZE)), posY + (TILESIZE - (posY % TILESIZE))});
    }
    else if (posX % TILESIZE != 0) {
        collisionBlock.push_back({posX - (posX % TILESIZE), posY});
        collisionBlock.push_back({posX + (TILESIZE - (posX % TILESIZE)), posY});
    }
    else if (posY % TILESIZE != 0) {
        collisionBlock.push_back({posX, posY - (posY % TILESIZE)});
        collisionBlock.push_back({posX, posY + (TILESIZE - (posY % TILESIZE))});
    }
    else {
        collisionBlock.push_back(coordinate);
    }
    return collisionBlock;
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

vector<string> Entities::getValidMove(vector<vector<vector<Tile> > >& game_map) {
    vector<string> result;
    for (string move_way : validStatus) {
        string move_back = "";
        if (move_way == "down") move_back = "up";
        else if (move_way == "up") move_back = "down";
        else if (move_way == "left") move_back = "right";
        else move_back = "left";

        send_move(move_way);
        
        bool isok = true;
        vector<SDL_Point> collision = getCollision();
        for (SDL_Point& collisionCoordinate : collision) {
            for (int layer = 0; layer <= 2; layer++) {
                Tile& tile = game_map[layer][collisionCoordinate.y / TILESIZE][collisionCoordinate.x / TILESIZE];
                if (tile.groupCheck["walkon"] == false) {
                    send_move(move_back);
                    isok = false;
                    break;
                }
            }
        }
        if (isok == true) result.push_back(move_way);
    }
    return result;
}

int Entities::getMoveTime() {
    return move_time;
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