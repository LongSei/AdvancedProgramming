// Unoptimized 
#include<bits/stdc++.h>
using namespace std;
struct StructWithPointer {
    int* data;

    StructWithPointer(int value) {
        data = new int(value);
    }
    void printStruct() {
        cout << *data << " " << data << endl;
    }
};

int main() {
    StructWithPointer x(10);
    x.printStruct();
    StructWithPointer y = x;
    y.printStruct();
}