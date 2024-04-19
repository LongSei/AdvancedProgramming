#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

void printValue(Point p) {
    cout << &p << endl;
}

void printReference(const Point &p) {
    cout << &p << endl;
}

int main() {
    Point p1 = {10, 20};

    cout << &p1 << endl;
    printValue(p1);
    printReference(p1);
}
