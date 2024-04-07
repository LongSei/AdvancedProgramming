#ifndef engine_hpp
#define engine_hpp

#include<bits/stdc++.h>
#include<random>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"./company_tools/chatbox.hpp"
#include"./company_tools/manager.hpp"
#include"essential.hpp"
#include"constant.hpp"
#include"grid.hpp"
class CameraScreen {
    public: 
        CameraScreen();
        CameraScreen(SDL_Renderer* renderer);
        void customDraw(Characters& player, vector<map<int, map<int, Tile>>>& game_map);
        void calculateVisibleArea(const SDL_Point& center);
    private: 
        SDL_Renderer* renderer;
        SDL_Texture* floor_surf;
        SDL_Rect floor_rect;
        SDL_Point half_screen;
};

class Game {
    public:
        void init(bool fullscreen, int width, int height, const char* title);
        void handleEvents(SDL_Event event);
        void renderUpdate();
        void renderClear();
        void clean();
        bool running();
        void createMap();

    private: 
        bool isRunning;
        Uint32 startTime;
        SDL_Window* window;
        SDL_Renderer* renderer;
        EntitiesManager mainManager;
        vector<map<int, map<int, Tile>>> game_map;
        bool IS_FULLSCREEN;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        const char* SCREEN_TITLE;
        CameraScreen ScreenCamera;
        Characters mainPlayer;
};

#endif