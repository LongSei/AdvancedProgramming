#ifndef essential_hpp
#define essential_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<filesystem>
#include <random>
#include <stdexcept>
using namespace std;

class EssentialFunction {
    public:
        vector<string> split(const string &s, char delimiter);
        vector<vector<string> > read_csv(string file_directory);
        SDL_Texture* loadTexture (const string& path, SDL_Renderer* renderer);
        SDL_Texture* loadFont (TTF_Font* font, int size, const SDL_Color& color, string&, SDL_Renderer* renderer);
        vector<SDL_Texture*> read_image_folder(string& path, SDL_Renderer* renderer);
        template <typename AUTO_TYPE> 
        AUTO_TYPE choice(const vector<AUTO_TYPE>& vec) {
            if (vec.empty()) {
                throw invalid_argument("Cannot select an element from an empty vector.");
            }
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> distrib(0, vec.size() - 1);
            return vec[distrib(gen)];
        }
        int randint(int min_number, int max_number);
};
#endif