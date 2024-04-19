#include <bits/stdc++.h>
using namespace std;

bool binarySearch(int* start, int* end, int value) {
    if (start > end) {
        return false;
    }
    int* mid = start + (end - start) / 2;
    // Phép toán (start + end) / 2.
    // Khi làm việc với con trỏ, việc sử dụng phép toán này có thể không an toàn và dẫn đến hành vi không xác định
    
    if (*mid == value) {
        return true;
    } else if (*mid > value) {
        return binarySearch(start, mid - 1, value);
    } else {
        return binarySearch(mid + 1, end, value);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* start = arr;
    int* end = arr + (sizeof(arr) / sizeof(arr[0])) - 1;
    int valueToFind = 5;

    if (binarySearch(start, end, valueToFind)) {
        cout << valueToFind << " founded" << endl;
    } else {
        cout << valueToFind << "can not be founded" << endl;
    }
    return 0;
}
