#include <iostream>
using namespace std;

struct Point {
    int x;
    int* y;
};

int main() {
    int yValue = 20;
    Point p1 = {10, &yValue};
    Point p2 = p1; // Copy nông

    cout << "p1.x: " << p1.x << ", *p1.y: " << *(p1.y) << endl;
    cout << "p2.x: " << p2.x << ", *p2.y: " << *(p2.y) << endl;

    yValue = 30; // Thay đổi giá trị thông qua yValue sẽ ảnh hưởng đến cả p1 và p2
    cout << "Sau sửa" << endl;
    cout << "p1.x: " << p1.x << ", *p1.y: " << *(p1.y) << endl;
    cout << "p2.x: " << p2.x << ", *p2.y: " << *(p2.y) << endl;

    return 0;
}
