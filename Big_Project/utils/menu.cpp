#include"menu.hpp"

Items::Items() {
    image_directory = "";
}

Items::Items(string& _image_directory, map<string, float>& _effect) {
    image_directory = image_directory;
    effect = effect; 
}

Menu::Menu() {
    renderer = nullptr;
    items.clear();
    menu_rect = ITEM_MENU;
    menu_valid_space = ITEM_MENU;
}

Menu::Menu(SDL_Renderer* _renderer, vector<Items>& _items, SDL_Rect& _menu_rect) {
    renderer = _renderer; 
    items = _items;
    menu_rect = _menu_rect;
    menu_valid_space = {menu_rect.x + MARGIN_ITEM_MENU.x, menu_rect.y + MARGIN_ITEM_MENU.y, menu_rect.w + MARGIN_ITEM_MENU.w, menu_rect.h + MARGIN_ITEM_MENU.h};
    menu_grid_sizes = {(menu_valid_space.x + menu_valid_space.w) / ITEM_SIZE, (menu_valid_space.y + menu_valid_space.h) / ITEM_SIZE};
}

void Menu::render() {
    int amount_item = items.size();

    bool isDone = false;
    for (int row = 0; row < menu_grid_sizes[0]; row++) {
        if (isDone) {break;}
        for (int col = 0; col < menu_grid_sizes[1]; col++) {
            bool IS_APPEND_ALL_ITEM = (row * col + col <= amount_item ? true : false);
            
            if (IS_APPEND_ALL_ITEM) {
                Items& item_data = items[row * col + col];

                SDL_Texture* image = EssentialFunction().loadTexture(item_data.image_directory.c_str(), renderer);

                SDL_Rect item_rect = {menu_valid_space.x + col * ITEM_SIZE, menu_valid_space.y + row * ITEM_SIZE, ITEM_SIZE, ITEM_SIZE};
                item_rect = {item_rect.x + MARGIN_GRID_ITEM_MENU.x, item_rect.y + MARGIN_GRID_ITEM_MENU.y, item_rect.w + MARGIN_GRID_ITEM_MENU.w, item_rect.h + MARGIN_GRID_ITEM_MENU.h};

                SDL_RenderCopy(renderer, image, NULL, &item_rect);

            }
            else {
                isDone = true;
                break;
            }
        }
    }
}
