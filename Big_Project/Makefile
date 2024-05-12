MAIN_FILE=main.cpp
OUTPUT_FILE=GameOutput

UTILS_INCLUDE= ./utils/engine.cpp ./utils/characters.cpp ./utils/essential.cpp ./utils/constant.cpp ./utils/grid.cpp ./utils/entities.cpp

# SDL2 include and library paths
SDL_INCLUDE=-I/opt/homebrew/Cellar/sdl2/2.30.3/include/SDL2
SDL_LIB=-L/opt/homebrew/Cellar/sdl2/2.30.3/lib -lSDL2

# SDL2_image include and library paths
SDL_IMAGE_INCLUDE=-I/opt/homebrew/Cellar/sdl2_image/2.8.2_1/include/SDL2
SDL_IMAGE_LIB=-L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib -lSDL2_image

# SDL2_ttf include and library paths
SDL_TTF_INCLUDE=-I/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2
SDL_TTF_LIB=-L/opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib -lSDL2_ttf

hellomake: 
	clang++ -std=c++17 $(MAIN_FILE) $(UTILS_INCLUDE) -o $(OUTPUT_FILE) $(SDL_INCLUDE) $(SDL_LIB) $(SDL_IMAGE_INCLUDE) $(SDL_IMAGE_LIB) $(SDL_TTF_INCLUDE) $(SDL_TTF_LIB) && ./$(OUTPUT_FILE)