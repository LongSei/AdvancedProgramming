#include "essential.hpp"

vector<string> EssentialFunction::split(const string &s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
}

vector<vector<string>> EssentialFunction::read_csv(string file_directory) {
    ifstream file(file_directory);
    string line;
    vector<vector<string>> result;
    result.clear();


    if (!file.is_open()) {
        cout << "Could not open the file - '" << file_directory << "'" << endl;
        return result;
    }
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        result.push_back(tokens);
    }
    file.close();
    return result;
}

SDL_Texture* EssentialFunction::loadTexture(const string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

vector<SDL_Texture*> EssentialFunction::read_image_folder(string& path, SDL_Renderer* renderer) {
    vector<SDL_Texture*> result;
    try {
        if (filesystem::is_directory(path)) {
            for (const auto& entry : filesystem::directory_iterator(path)) {
                string filename = entry.path().filename().string();
                string file_directory = path + "/" + filename;
                result.push_back(loadTexture(file_directory, renderer));
            }
        }
    } 
    catch (const filesystem::filesystem_error& error) {
        cerr << error.what() << '\n';
    }
    return result;
}

int EssentialFunction::randint(int min_number, int max_number) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_number, max_number);
    return dis(gen);
}

SDL_Texture* EssentialFunction::loadFont(TTF_Font* font, int size, const SDL_Color& color, string& text, SDL_Renderer* renderer) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (text_texture == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface(text_surface);
    return text_texture;
}