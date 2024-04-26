#ifndef engine_hpp
#define engine_hpp

#include<bits/stdc++.h>
#include<random>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"characters.hpp"
#include"essential.hpp"
#include"constant.hpp"
#include"grid.hpp"
#include"menu.hpp"
#include"entities.hpp"

class CameraScreen {
    public: 
        CameraScreen();
        CameraScreen(SDL_Renderer* renderer);
        void mapDraw(MultiDimVector<Tile, 3>& game_map);
        void playerDraw(Characters& player);
        void entitiesDraw(MultiDimVector<Entities, 2> game_entities);
        void calculateVisibleArea(const SDL_Point& center);
        void status_bar(Characters& player, Uint32 startTime); 
    private: 
        int MAP_WIDTH;
        int MAP_HEIGHT;
        SDL_Renderer* renderer;
        SDL_Texture* floor_surf;
        SDL_Rect floor_rect;
        SDL_Point half_screen;
};

class Game {
    public:
        void init(bool fullscreen, int width, int height, const char* title, Characters _mainPlayer);
        void handleEvents(SDL_Event event);
        void renderUpdate();
        void clean();
        bool running();
        void createMap();
        void createEntities(Characters& player);
        void playerHandle(string move_back);
        void enemiesHandle();
        SDL_Renderer* renderer;

    private: 
        bool isRunning;
        Uint32 startTime;
        SDL_Window* window;

        MultiDimVector<Tile, 3> game_map;
        MultiDimVector<Entities, 2> game_entities;
        bool IS_FULLSCREEN;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        const char* SCREEN_TITLE;

        CameraScreen ScreenCamera;
        Characters mainPlayer;
};

class DropdownMenu {
    private: 
        
        
    public: 

};

#endif