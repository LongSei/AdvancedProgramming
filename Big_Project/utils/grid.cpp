#include"grid.hpp"
using namespace std;

Grid::Grid() {
    posX = 0;
    posY = 0;
}

Grid::Grid(int _posX, int _posY) {
    posX = _posX;
    posY = _posY;
}

Tile::Tile() {
    image = nullptr;
    box = Grid();
}

Tile::Tile(SDL_Texture* _image, map<string, bool>& _groupCheck, int posX, int posY) {
    if (groupCheck["visible"] == true && _image == NULL) {
        SDL_Log("Cannot import Image of visible Tile");
    } 
    else {
        image = _image; 
        groupCheck = _groupCheck;
        box = Grid(posX, posY);
    }
}

bool Tile::checkCollision(Tile& b) {
    int leftA = box.posX;
    int rightA = box.posX + TILESIZE;
    int topA = box.posY;
    int bottomA = box.posY + TILESIZE;

    int leftB = b.box.posX;
    int rightB = b.box.posX + TILESIZE;
    int topB = b.box.posY;
    int bottomB = b.box.posY + TILESIZE;

    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }
    return true;
}