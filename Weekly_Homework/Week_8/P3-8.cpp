#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    Point p1 = {10, 20};

    cout << "Địa chỉ p1: " << &p1 << endl;
    cout << "Địa chỉ p1.x: " << &(p1.x) << endl;
    cout << "Địa chỉ p1.y: " << &(p1.y) << endl;

    return 0;
}

// Địa chỉ của attribute đầu tiên bằng địa chỉ của Point