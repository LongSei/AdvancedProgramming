#include"../entities/characters.hpp"
#include"../company_tools/manager.hpp"
using namespace std;

void Characters::init(string _position, pair<int, int> _coordinate, string _status, SDL_Renderer* renderer) {
    position = _position;
    if (validPosition.find(position) == validPosition.end()) {
        SDL_Log("Position Error with Character");
        SDL_Quit();
        return;
    }
    string directory = "./images/" + position + ".png";
    avatar = IMG_LoadTexture(renderer, directory.c_str());
    if (!avatar) {
        SDL_Log("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }
    coordinate = _coordinate;
    status = _status;
}

void Characters::render(Uint32 GameStartTime, SDL_Renderer* renderer) {
    if (validStatus.find((*this).status) == validStatus.end()) {
        SDL_Log("Status Error with Character");
        SDL_Quit();
        return;
    }
    int avatarWidth, avatarHeight;
    SDL_QueryTexture(avatar, NULL, NULL, &avatarWidth, &avatarHeight);
    SDL_Rect dstRect = {coordinate.first, coordinate.second, avatarWidth, avatarHeight};

    Uint32 currentTime = SDL_GetTicks();
    float timeElapsed = (currentTime - GameStartTime) / 1000.0f;
    dstRect.y = coordinate.second + abs(round((sin(timeElapsed * breathingSpeed)))) * breathingAmplitude;
    SDL_RenderCopy(renderer, avatar, NULL, &dstRect);
}

