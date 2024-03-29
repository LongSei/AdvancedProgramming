#include <bits/stdc++.h>
using namespace std;

struct Point {
    float x, y;
    void print() {
        cout << x << ", " << y << endl;
    }
};

Point mid_point(Point a, Point b) {
    Point mid;
    mid.x = (a.x + b.x) / 2;
    mid.y = (a.y + b.y) / 2;
    return mid;
}


int main() {
    Point point;
    point.x = 10;
    point.y = 12;
    Point point2; 
    point2.x = 15;
    point2.y = 20;

    Point midPoint;
    midPoint = mid_point(point, point2);
    midPoint.print();
}