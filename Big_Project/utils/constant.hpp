#ifndef constant_hpp
#define constant_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include"essential.hpp"

// COLOR
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};

// GAME WINDOW
const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;
const string ASSET_DIRECTORY = "./assets/graphics/";
const string FONT_PATH = "./assets/graphics/font/joystix.ttf";
const int GAME_OVER_FONT_SIZE = 80;
const SDL_Color GAME_OVER_FONT_COLOR = BLACK;
const string GAME_OVER_IMAGE = "./assets/graphics/game_over_background.png";
const int GAME_OVER_MARGIN = 10;

// MAP
const int TILESIZE = 64;
const int MAP_IMAGE_WIDTH = 3648;
const int MAP_IMAGE_HEIGHT = 3200;
const string backgroundMap = "./assets/graphics/tilemap/ground.png";
const string list_layouts[] = {"./assets/map/map_FloorBlocks.csv", "./assets/map/map_Grass.csv", "./assets/map/map_Objects.csv", "./assets/map/map_Entities.csv"};
const string list_graphics[] = {"./assets/graphics/grass", "./assets/graphics/objects"};
const Uint32 GAME_START_TIME = 0;
const vector<string> POSSIBLE_MOVES = {"up", "down", "left", "right"};

// PLAYER STATUS
const string PLAYER_DIRECTORY = "./assets/graphics/player/";
const SDL_Point PLAYER_SPAWNER = {1280, 1280};
const int PLAYER_SPEED = 32;
const float PLAYER_ENERGY = 20;
const float PLAYER_HEALTH = 100;
const float ATTACK_COST = 5;
const int SCORE_MARGIN = 10;
const int SCORE_FONT_SIZE = 20;
const SDL_Color SCORE_FONT_COLOR = WHITE;

// PLAYER GRAPHIC
const SDL_Rect HEALTH_BAR = {0,0,400,25};
const SDL_Rect ENERGY_BAR = {0,30,300,25};
const SDL_Color HEALTH_COLOR = RED;  
const SDL_Color ENERGY_COLOR = BLUE;  
const float HEALTH_ACCELERATE = 20;
const float ENERGY_ACCELERATE = 20; 
const Uint32 expectedTime = 3; 
const float tolerance = 0.05;     

// ITEM GRAPHIC
const int ITEM_SIZE = 64;
const SDL_Rect ITEM_MENU = {128, 64, 1024, 600};
const SDL_Rect MARGIN_ITEM_MENU = {ITEM_SIZE, ITEM_SIZE, ITEM_SIZE, ITEM_SIZE}; 
const SDL_Rect MARGIN_GRID_ITEM_MENU = {10, 10, 10, 10};
const vector<string> ITEM_NAME = {"axe", "lance", "rapier", "sai", "sword"};
const map<string, string> ITEM_PATH = 
                                    {
                                        {"axe", "./assets/graphics/weapons/axe"},
                                        {"lance", "./assets/graphics/weapons/lance"},
                                        {"rapier", "./assets/graphics/weapons/rapier"},
                                        {"sai", "./assets/graphics/weapons/sai"},
                                        {"sword", "./assets/graphics/weapons/sword"}
                                    };

// ENTITIES STATUS
const string ENEMIES_DIRECTORY = "./assets/graphics/monsters/";
const map<string, map<string, float>> ENEMIES_STAT = {
    {"bamboo", {{"HEALTH", 10}, {"DAMAGE", 20}, {"SPEED", 16}, {"MOVE TIME", 1}, {"ATTACK TIME", 1}}},
    {"spirit", {{"HEALTH", 20}, {"DAMAGE", 15}, {"SPEED", 16}, {"MOVE TIME", 1}, {"ATTACK TIME", 1}}},
    {"squid", {{"HEALTH", 30}, {"DAMAGE", 25}, {"SPEED", 16}, {"MOVE TIME", 1}, {"ATTACK TIME", 1}}},
};
const vector<string> ENIMIES_NAME = {"bamboo", "spirit", "squid"};
const pair<int, int> RANGE_ENEMY_OFF_SET_X = {-5, 5};
const pair<int, int> RANGE_ENEMY_OFF_SET_Y = {-5, 5};
const float TOLERANCE_ENEMY_MOVE = 0.05;
const float TOLERANCE_ENEMY_ATTACK = 0.05;
const int ENIMIES_MARGIN_WITH_BAR = 15;
const int ENIMIES_HEALTH_BAR_HEIGHT = 5;

// GAME ENTITIES
const int ENTITIES_SPAWN_TIME = 3;
const vector<int> RANDOM_AMOUNT_ENTITIES = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2};
const float ENTITIES_SPAWN_TOLERANCE = 0.05;
#endif