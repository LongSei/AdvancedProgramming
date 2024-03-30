#include<bits/stdc++.h>
using namespace std;

int arr[4] = {1,2,3,4};

int main() {
    int brr[4] = {1,2,3,4};
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        cout << brr[i] << " ";
    }
}

// Nếu N < 4, lỗi do mảng khai báo bị tràn
// Nếu N > 4, khai báo 4 phần tử đầu, phần từ sau sẽ khai báo ngẫu nhiên