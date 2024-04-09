#ifndef constant_hpp
#define constant_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"./company_tools/chatbox.hpp"
#include"./company_tools/manager.hpp"
#include"essential.hpp"

const int TILESIZE = 64;
const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;
const string backgroundMap = "./assets/graphics/tilemap/ground.png";
const string list_layouts[] = {"./assets/map/map_FloorBlocks.csv", "./assets/map/map_Grass.csv", "./assets/map/map_Objects.csv", "./assets/map/map_Entities.csv"};
const string list_graphics[] = {"./assets/graphics/grass", "./assets/graphics/objects"};
const Uint32 GAME_START_TIME = 0;

const string PLAYER_DIRECTORY = "./assets/graphics/player/down/down_0.png";
const SDL_Point PLAYER_SPAWNER = {1280, 1280};
const int PLAYER_SPEED = 64;

#endif