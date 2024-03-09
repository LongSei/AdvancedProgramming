MAIN_FILE=test.cpp
OUTPUT_FILE=GameOutput

UTILS_INCLUDE= ./utils/engine.cpp

# SDL2 include and library paths
SDL_INCLUDE=-I/opt/homebrew/Cellar/sdl2/2.30.0/include/SDL2
SDL_LIB=-L/opt/homebrew/Cellar/sdl2/2.30.0/lib -lSDL2

# SDL2_image include and library paths
SDL_IMAGE_INCLUDE=-I/opt/homebrew/Cellar/sdl2_image/2.8.2/include/SDL2
SDL_IMAGE_LIB=-L/opt/homebrew/Cellar/sdl2_image/2.8.2/lib -lSDL2_image

# SDL2_gfx include and library paths
SDL_GFX_INCLUDE=-I/opt/homebrew/Cellar/sdl2_gfx/1.0.4/include/SDL2
SDL_GFX_LIB=-L/opt/homebrew/Cellar/sdl2_gfx/1.0.4/lib -lSDL2_gfx

hellomake: 
	clang++ $(MAIN_FILE) $(UTILS_INCLUDE) -o $(OUTPUT_FILE) $(SDL_INCLUDE) $(SDL_LIB) $(SDL_IMAGE_INCLUDE) $(SDL_IMAGE_LIB) $(SDL_GFX_INCLUDE) $(SDL_GFX_LIB) && ./$(OUTPUT_FILE)