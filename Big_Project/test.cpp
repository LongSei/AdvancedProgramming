#include"./utils/engine.hpp"
#include<bits/stdc++.h>
using namespace std;

void modify(int* a) {
    *a = 20;
}

int main() {
    int* a = new int;
    cout << a << " " << *a << endl;
    *a = 10;
    vector<int*> arr;
    arr.push_back(a);
    cout << *arr[0] << endl;
    modify(a);
    cout << *arr[0];
}