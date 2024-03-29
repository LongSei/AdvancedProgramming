#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    void print() {
        cout << x << ", " << y << endl;
    }
};

void modify_by_value(Point p) {
    p.x += 5;
    p.y += 5;
}

void modify_by_reference(Point& p) {
    p.x = 0;
    p.y = 0;
}

int main() {
    Point point;
    point.x = 10;
    point.y = 12;
    modify_by_value(point);
    point.print();
    modify_by_reference(point);
    point.print();
}
