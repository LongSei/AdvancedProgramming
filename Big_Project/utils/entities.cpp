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
    coordinate = _coordinate;
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
    if (status_index == 1) {
        attack_coordinate.y -= TILESIZE;
    }
    else if (status_index == 0) {
        attack_coordinate.y += TILESIZE;
    }
    else if (status_index == 2) {
        attack_coordinate.x -= TILESIZE;
    }
    else if (status_index == 3) {
        attack_coordinate.x += TILESIZE;
    }
    SDL_Point playerCoordinate = player.getCoordinate();
    if (playerCoordinate.x == attack_coordinate.x && playerCoordinate.y == attack_coordinate.y) {
        isSendAttack = true;
        return attack_coordinate;
    }
    return {0,0};
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
    if (status == move_way) {
        status_index = (status_index + 1) % 4;
    }
    else {
        status = move_way;
        status_index = 0;
    }
}