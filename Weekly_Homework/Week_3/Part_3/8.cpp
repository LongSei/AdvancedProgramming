#include<bits/stdc++.h>
using namespace std;

struct Point {
    float x, y;

    Point(float _x, float _y) : x(_x), y(_y) {}
    Point() : x(0), y(0) {}

    void printAddress() {
        cout << &x << " " << &y << endl;
    }
};

struct Rect {
    float x, y, w, h;

    bool contains(const Point& p) const {
        return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h;
    }
};

signed main() {
    Point x (1, 2); 
    x.printAddress();
}