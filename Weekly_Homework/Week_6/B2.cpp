#include<bits/stdc++.h>
using namespace std;

bool eq(int arr1[], int arr2[], int n) {
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int count = 0;
    int ptrJ = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = ptrJ; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                count += 1;
                ptrJ = j + 1;
                break;
            }
        }
    }
    return count == n;
}
