#include <bits/stdc++.h>
using namespace std;

int main() {
    char daytab[2][12] = {
        {31,28,31,30,31,30,31,31,30,31,30,31},
        {31,29,31,30,31,31,30,31,30,31,30,31}
    };

    char daytab2[2][12] = {
        31,28,31,30,31,30,31,31,30,31,30,31,
        31,29,31,30,31,30,31,31,30,31,30,31
    };

    char daytab3[20][20] = {
        {31,28,31,30,31,30,31,31,30,31,30,31},
        {31,29,31,30,31,31,30,31,30,31,30,31}
    };


    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 12; ++j) {
            cout << to_string(daytab[i][j]) << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 12; ++j) {
            cout << to_string(daytab2[i][j]) << " ";
        }
        cout << endl;
    }
}
