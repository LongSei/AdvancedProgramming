#include"../entities/characters.hpp"
#include"../company_tools/manager.hpp"
#include"../constant.hpp"
using namespace std;

Characters::Characters() {
    position = "";
    coordinate = {0,0};
    status = "down";
    speed = 0;
}

Characters::Characters(string _image_directory, string _position, SDL_Point _coordinate, string _status, int _speed, SDL_Renderer* _renderer) {
    position = _position;
    image = EssentialFunction().loadTexture(_image_directory, _renderer);
    if (validPosition.find(position) == validPosition.end()) {
        SDL_Log("Position Error with Character");
        SDL_Quit();
        return;
    }
    coordinate = _coordinate;
    status = _status;
    speed = _speed;
}

void Characters::render(SDL_Renderer* renderer, SDL_Point renderPosition) {
    if (validStatus.find((*this).status) == validStatus.end()) {
        SDL_Log("Status Error with Character");
        SDL_Quit();
        return;
    }
    SDL_Rect dstRect = {renderPosition.x, renderPosition.y, TILESIZE, TILESIZE};

    // Uint32 currentTime = SDL_GetTicks();
    // float timeElapsed = (currentTime - GAME_START_TIME) / 1000.0f;
    // dstRect.y = coordinate.y + abs(round((sin(timeElapsed * breathingSpeed)))) * breathingAmplitude;
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
    if (posX % 64 != 0 && posY % 64 != 0) {
        collisionBlock.push_back({posX - (posX % 64), posY - (posY % 64)});
        collisionBlock.push_back({posX - (posX % 64), posY + (64 - (posY % 64))});
        collisionBlock.push_back({posX + (64 - (posX % 64)), posY - (posY % 64)});
        collisionBlock.push_back({posX + (64 - (posX % 64)), posY - (64 - (posY % 64))});
    }
    else if (posX % 64 != 0) {
        collisionBlock.push_back({posX - (posX % 64), posY});
        collisionBlock.push_back({posX - (64 - (posX % 64)), posY});
    }
    else if (posY % 64 != 0) {
        collisionBlock.push_back({posX, posY - (posY % 64)});
        collisionBlock.push_back({posX, posY - (64 - (posY % 64))});
    }
    else {
        collisionBlock.push_back(coordinate);
    }
    return collisionBlock;
}

void Characters::move(const string& move_way) {
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
    else {
        SDL_Log("Move Way Error !!!");
    }
}