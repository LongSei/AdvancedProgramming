#include"../entities/characters.hpp"
#include"../company_tools/manager.hpp"
#include"../constant.hpp"
using namespace std;

Characters::Characters() {
    position = "";
    coordinate = {0,0};
    status = "down";
}

Characters::Characters(string image_directory, string _position, SDL_Point _coordinate, string _status, SDL_Renderer* renderer) {
    position = _position;
    image = EssentialFunction().loadTexture(image_directory, renderer);
    if (validPosition.find(position) == validPosition.end()) {
        SDL_Log("Position Error with Character");
        SDL_Quit();
        return;
    }
    coordinate = _coordinate;
    status = _status;
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