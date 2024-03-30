#include<bits/stdc++.h>
using namespace std;

char arr[5] = "abcd";

int main() {
    char brr[5] = "abcd";
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        cout << brr[i] << " ";
    }
}

// Nếu N < 5, lỗi do mảng khai báo bị tràn
// Nếu N > 5, khai báo 4 phần tử đầu, phần từ sau sẽ khai báo ngẫu nhiên