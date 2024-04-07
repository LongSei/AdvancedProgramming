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
    object_type = "";
    isShown = false;
    box = Grid();
}

Tile::Tile(SDL_Texture* _image, string _object_type, bool _isShown, int posX, int posY) {
    if (_isShown == true && _image == NULL) {
        cout << "ERROR: " << _object_type << endl;
        SDL_Log("Cannot import Image of visible Tile");
    } 
    else {
        image = _image; 
        object_type = _object_type;
        box = Grid(posX, posY);
        isShown = _isShown;
    }
}

bool Tile::checkCollision(Tile& b) {
    // Calculate the sides of rect A
    int leftA = box.posX;
    int rightA = box.posX + TILESIZE;
    int topA = box.posY;
    int bottomA = box.posY + TILESIZE;

    // Calculate the sides of rect B
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