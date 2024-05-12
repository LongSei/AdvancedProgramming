#ifndef engine_hpp
#define engine_hpp

#include<bits/stdc++.h>
#include<random>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
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
        void mapDraw(vector<vector<vector<Tile> > >& game_map);
        void playerDraw(Characters& player);
        void entitiesDraw(Entities& enemy);
        void calculateVisibleArea(const SDL_Point& center);
        void status_bar(Characters& player, Uint32 startTime); 
        void score_show(Characters& player);
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
        void init(bool fullscreen, int width, int height, const char* title, Characters& _mainPlayer);
        void handleEvents(SDL_Event event);
        void renderUpdate();
        void clean();
        bool running();
        void createMap();
        void createEntities();
        void playerHandle(const string& move_back);
        void entitiesHandle();
        bool stopping();
        void gameOverScreen();
        void playerClearEntity();
        SDL_Renderer* renderer;

    private: 
        bool isRunning;
        bool isStopping;
        Uint32 startTime;
        SDL_Window* window;

        vector<vector<vector<Tile> > > game_map;
        vector<Entities> game_entities;
        int amount_entities = 1;
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