#include"characters.hpp"
using namespace std;

Characters::Characters() {
    coordinate = {0,0};
    status = "down";
    speed = 0;
    damage = 10;
}

Characters::Characters(string _position, SDL_Point _coordinate, string _status, int _speed) {
    coordinate = _coordinate;
    status = _status;
    speed = _speed;
    damage = 10;
}

void Characters::render(SDL_Renderer* renderer, SDL_Point renderPosition) {
    SDL_Rect dstRect = {renderPosition.x, renderPosition.y, TILESIZE, TILESIZE};
    string _image_directory = "";
    if (isSendAttack == false) {
        _image_directory = PLAYER_DIRECTORY + status + "/" + status + "_" + to_string(status_index) + ".png";
    }
    else {
        _image_directory = PLAYER_DIRECTORY + status + "_attack" + "/" + "attack_" + status + ".png";
        isSendAttack = false;
    }
    image = EssentialFunction().loadTexture(_image_directory, renderer);
    SDL_RenderCopy(renderer, image, NULL, &dstRect);
}

SDL_Point Characters::getCoordinate() {
    return coordinate;
}

SDL_Point Characters::getCenter() {
    return {coordinate.x + TILESIZE / 2, coordinate.y + TILESIZE / 2};
}

vector<SDL_Point> Characters::getCollision() {
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

void Characters::send_move(const string& move_way) {
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

void Characters::update_move(const string& move_way) {
    if (status == move_way) {
        status_index = (status_index + 1) % 4;
    }
    else {
        status = move_way;
        status_index = 0;
    }
}

void Characters::undo_move(const string& move_way) {
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

pair<float, float> Characters::getAccelerate() {
    return pair<float, float>(max(float(0), exp(float(health_time_refill) / accHealth) - 1), max(float(0), exp(float(energy_time_refill) / accEnergy) - 1));
}

pair<float, float> Characters::getStatus() {
    return pair<float, float>(health, energy);
}

pair<float, float> Characters::getMaxStatus() {
    return pair<float, float>(maxHealth, maxEnergy);
}

void Characters::updateStatus() {
    if (isHealthDecrease == true) {
        health_time_refill = -5;
        isHealthDecrease = false;
    }
    else {
        pair<float, float> acc = getAccelerate();
        health = min(health + acc.first, maxHealth);
        health_time_refill += 1;
    }

    if (isEnergyDecrease == true) {
        energy_time_refill = -5;
        isEnergyDecrease = false;
    }
    else {
        pair<float, float> acc = getAccelerate();
        energy = min(energy + acc.second, maxEnergy);
        energy_time_refill += 1;
    }
}

SDL_Point Characters::send_attack() {
    SDL_Point attack_coordinate = coordinate;
    if (status == "up") {
        attack_coordinate.y -= TILESIZE;
    }
    else if (status == "down") {
        attack_coordinate.y += TILESIZE;
    }
    else if (status == "left") {
        attack_coordinate.x -= TILESIZE;
    }
    else if (status == "right") {
        attack_coordinate.x += TILESIZE;
    }
    if (energy >= ATTACK_COST) {
        energy -= 10;
        isEnergyDecrease = true;
        isSendAttack = true;
        return attack_coordinate;
    }
    return {0,0};
}

float Characters::getDamage() {
    return damage;
}

void Characters::takeDamage(float damage) {
    health -= damage;
    isHealthDecrease = true;
}

void Characters::takeExp() {
    experiance += 1;
    damage += 0.1;
    health += 1;
    energy += 1;
}