#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Rect {
    int x, y, w, h;

    bool contains(const Point& p) const {
        return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h;
    }
};

struct Ship {
    Rect boundingBox;
    string name;
    int dx, dy;

    void move() {
        boundingBox.x += dx;
        boundingBox.y += dy;
    }
};

void display(const Ship& ship) {
    cout << "Ship: " << ship.name
         << " Position: (" << ship.boundingBox.x << ", " << ship.boundingBox.y << ")"
         << " Dimensions: " << ship.boundingBox.w << "x" << ship.boundingBox.h << endl;
}

int main() {
    Ship ship1 = {{100, 100, 20, 10}, "Enterprise", 5, 3};
    Ship ship2 = {{200, 200, 30, 15}, "Voyager", -2, 4};

    int loop = 0;
    while (loop < 10) {
        ship1.move();
        ship2.move();
        display(ship1);
        display(ship2);
        loop++;
    }
}
