// #include <SDL2/SDL.h>
// #include <vector>
// #include <string>

// // Structure to hold menu options
// struct MenuItem {
//     std::string label;
//     SDL_Rect rect;  // Rectangle for the menu item
//     bool selected;  // Whether this item is currently selected

//     MenuItem(const std::string& text, int x, int y, int w, int h) :
//         label(text), rect{x, y, w, h}, selected(false) {}
// };

// // Class for Dropdown Menu
// class DropdownMenu {
// public:
//     SDL_Renderer* renderer;
//     std::vector<MenuItem> items;
//     bool isOpen;
//     SDL_Rect menuButton;  // Rectangle for the menu button

//     DropdownMenu(SDL_Renderer* rend, int x, int y, int w, int h) : renderer(rend), isOpen(false) {
//         menuButton = {x, y, w, h};
//     }

//     void addItem(const std::string& itemLabel) {
//         int itemHeight = 30;  // Height of each item in the dropdown
//         int x = menuButton.x, y = menuButton.y + menuButton.h + (items.size() * itemHeight), w = menuButton.w, h = itemHeight;
//         items.emplace_back(itemLabel, x, y, w, h);
//     }

//     void render() {
//         // Render the button that opens/closes the menu
//         SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
//         SDL_RenderFillRect(renderer, &menuButton);

//         // Render the text or a label for the button here (simplified as a rectangle)

//         if (isOpen) {
//             for (const auto& item : items) {
//                 SDL_SetRenderDrawColor(renderer, item.selected ? 255 : 200, item.selected ? 0 : 200, 200, 255);
//                 SDL_RenderFillRect(renderer, &item.rect);
//                 // Render the text for each item here (simplified as a rectangle)
//             }
//         }
//     }

//     void handleEvent(SDL_Event& e) {
//         if (e.type == SDL_MOUSEBUTTONDOWN) {
//             int x, y;
//             SDL_GetMouseState(&x, &y);

//             // Toggle menu open/close
//             if (x >= menuButton.x && x <= menuButton.x + menuButton.w &&
//                 y >= menuButton.y && y <= menuButton.y + menuButton.h) {
//                 isOpen = !isOpen;
//             } else if (isOpen) {
//                 for (auto& item : items) {
//                     if (x >= item.rect.x && x <= item.rect.x + item.rect.w &&
//                         y >= item.rect.y && y <= item.rect.y + item.rect.h) {
//                         item.selected = true;  // Select the item
//                         isOpen = false;  // Close the menu after selection
//                     } else {
//                         item.selected = false;  // Deselect other items
//                     }
//                 }
//             }
//         }
//     }
// };

// int main(int argc, char* args[]) {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window* window = SDL_CreateWindow("Dropdown Menu Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     DropdownMenu menu(renderer, 50, 50, 100, 30);
//     menu.addItem("Option 1");
//     menu.addItem("Option 2");
//     menu.addItem("Option 3");

//     bool running = true;
//     SDL_Event event;

//     while (running) {
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//             menu.handleEvent(event);
//         }

//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);

//         menu.render();

//         SDL_RenderPresent(renderer);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }






#include <SDL2/SDL.h>
#include <vector>
#include <string>

// Define a simple structure for inventory items
struct InventoryItem {
    std::string name;
    bool isSelected;
    SDL_Rect rect;

    InventoryItem(const std::string& name, int x, int y, int w, int h)
        : name(name), isSelected(false), rect{x, y, w, h} {}
};

// Class for the inventory menu
class InventoryMenu {
private:
    SDL_Renderer* renderer;
    std::vector<InventoryItem> items;
    int rows, cols;

public:
    InventoryMenu(SDL_Renderer* rend, int rows, int cols) : renderer(rend), rows(rows), cols(cols) {
        // Initialize a grid of inventory items
        int itemWidth = 50, itemHeight = 50, spacing = 10;
        int startX = 100, startY = 100;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int x = startX + j * (itemWidth + spacing);
                int y = startY + i * (itemHeight + spacing);
                items.emplace_back("Item " + std::to_string(i*cols + j + 1), x, y, itemWidth, itemHeight);
            }
        }
    }

    void render() {
        for (auto& item : items) {
            // Draw the item slot
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for item slot
            SDL_RenderFillRect(renderer, &item.rect);

            // Draw a border if selected
            if (item.isSelected) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for selected item border
                SDL_RenderDrawRect(renderer, &item.rect);
            }
        }
    }

    void selectItem(int index) {
        if (index >= 0 && index < items.size()) {
            for (auto& item : items) {
                item.isSelected = false; // Deselect all items
            }
            items[index].isSelected = true; // Select the specified item
        }
    }

    void handleEvent(SDL_Event& event) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            // Check if any item slots are clicked
            for (int i = 0; i < items.size(); ++i) {
                if (x >= items[i].rect.x && x <= items[i].rect.x + items[i].rect.w &&
                    y >= items[i].rect.y && y <= items[i].rect.y + items[i].rect.h) {
                    selectItem(i);
                    break;
                }
            }
        }
    }
};

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Inventory Menu Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    InventoryMenu menu(renderer, 3, 4); // 3 rows, 4 columns of items

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            menu.handleEvent(event);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear the screen with black
        SDL_RenderClear(renderer);

        menu.render();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


// #include<bits/stdc++.h>
// #include"./utils/essential.hpp"
// using namespace std;

// int main() {
//     MultiDimVector<int, 3> darray;
//     vector<int> size = {1,2,3};
//     darray.resize(size);
//     cout << darray.size() << " " << darray[1].size() << " " << darray[2].size() <<
// }