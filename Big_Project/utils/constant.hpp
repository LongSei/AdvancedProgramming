#ifndef constant_hpp
#define constant_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"essential.hpp"

// GAME WINDOW
const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;

// MAP
const int TILESIZE = 64;
const int MAP_IMAGE_WIDTH = 3648;
const int MAP_IMAGE_HEIGHT = 3200;
const string backgroundMap = "./assets/graphics/tilemap/ground.png";
const string list_layouts[] = {"./assets/map/map_FloorBlocks.csv", "./assets/map/map_Grass.csv", "./assets/map/map_Objects.csv", "./assets/map/map_Entities.csv"};
const string list_graphics[] = {"./assets/graphics/grass", "./assets/graphics/objects"};
const Uint32 GAME_START_TIME = 0;

// PLAYER STATUS
const string PLAYER_DIRECTORY = "./assets/graphics/player/";
const SDL_Point PLAYER_SPAWNER = {1280, 1280};
const int PLAYER_SPEED = 32;
const float PLAYER_ENERGY = 20;
const float PLAYER_HEALTH = 100;
const float ATTACK_COST = 10;

// PLAYER GRAPHIC
const SDL_Rect HEALTH_BAR = {0,0,400,25};
const SDL_Rect ENERGY_BAR = {0,30,400,25};
const SDL_Color HEALTH_COLOR = {255, 0, 0, 255};  // Red
const SDL_Color ENERGY_COLOR = {0, 0, 255, 255};  // Blue
const float HEALTH_ACCELERATE = 20;
const float ENERGY_ACCELERATE = 20; 
const Uint32 expectedTime = 10; // 1 second in milliseconds
const Uint32 tolerance = 1;      // Tolerance threshold in milliseconds

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
    {"bamboo", {{"HEALTH", 50}, {"DAMAGE", 20}, {"SPEED", 3.0}}},
    {"spirit", {{"HEALTH", 70}, {"DAMAGE", 15}, {"SPEED", 4.0}}},
    {"squid", {{"HEALTH", 60}, {"DAMAGE", 25}, {"SPEED", 2.5}}},
    {"raccoon", {{"HEALTH", 40}, {"DAMAGE", 30}, {"SPEED", 3.5}}}
};
const vector<string> ENIMIES_NAME = {"bamboo", "spirit", "squid", "raccoon"};
const pair<int, int> rangeEnemyOffSetX = {-5, 5};
const pair<int, int> rangeEnemyOffSetY = {-5, 5};
#endif