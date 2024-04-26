#ifndef grid_hpp
#define grid_hpp 

#include"constant.hpp"
using namespace std; 

class Grid {
    public: 
        Grid();
        Grid(int x, int y);
        int posX;
        int posY;
};

class Tile {
    public: 
        bool checkCollision(Tile& b);
        Tile();
        Tile(SDL_Texture* _image, map<string, bool>& groupCheck, int x, int y);

        SDL_Texture* image; 
        Grid box;
        map<string, bool> groupCheck = {{"visible", false}, 
                                        {"attackable", false}, 
                                        {"walkon", true}};
};

#endif 