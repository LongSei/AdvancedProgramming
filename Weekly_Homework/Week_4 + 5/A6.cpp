#include<bits/stdc++.h>
using namespace std;
int arr[31];

int main() {
    for (int i = 1; i <= 30; i++) {
        arr[i] = rand() % 101;
    }
    for (int i = 1; i <= 30; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 30 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    for (int i = 1; i <= 30; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}