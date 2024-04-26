#ifndef menu_hpp
#define menu_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"grid.hpp"
#include"essential.hpp"
#include"constant.hpp"
using namespace std;


class Items {
    public:
        string image_directory;
        map<string, float> effect; 

        Items();
        Items(string& image_directory, map<string, float>& effect);
};

class Menu {
    private: 
        SDL_Renderer* renderer;
        vector<Items> items;
        SDL_Rect menu_rect;
        SDL_Rect menu_valid_space;
        vector<int> menu_grid_sizes;

    public: 
        Menu();
        Menu(SDL_Renderer* _renderer, vector<Items>& _items, SDL_Rect& _menu_rect);
        void render();
};

#endif