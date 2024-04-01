MAIN_FILE=main.cpp
OUTPUT_FILE=GameOutput

UTILS_INCLUDE= ./utils/engine.cpp ./company_tools/manager.cpp ./company_tools/chatbox.cpp ./entities/characters.cpp

# SDL2 include and library paths
SDL_INCLUDE=-I/opt/homebrew/Cellar/sdl2/2.30.1/include/SDL2
SDL_LIB=-L/opt/homebrew/Cellar/sdl2/2.30.1/lib -lSDL2

# SDL2_image include and library paths
SDL_IMAGE_INCLUDE=-I/opt/homebrew/Cellar/sdl2_image/2.8.2_1/include/SDL2
SDL_IMAGE_LIB=-L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib -lSDL2_image

hellomake: 
	clang++ -std=c++14 $(MAIN_FILE) $(UTILS_INCLUDE) -o $(OUTPUT_FILE) $(SDL_INCLUDE) $(SDL_LIB) $(SDL_IMAGE_INCLUDE) $(SDL_IMAGE_LIB) $(SDL_GFX_INCLUDE) $(SDL_GFX_LIB) && ./$(OUTPUT_FILE)