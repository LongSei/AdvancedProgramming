#include <bits/stdc++.h>
using namespace std;

int count_even(int* arr, int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int count = count_even(arr, 5); // Đếm số chẵn trong 5 phần tử đầu tiên
    cout << count << endl;
    
    count = count_even(arr + 5, 5); // Đếm số chẵn trong 5 phần tử cuối cùng
    cout << count << endl;
    
}
