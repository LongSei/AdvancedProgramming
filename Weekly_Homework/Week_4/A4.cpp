// A
#include <bits/stdc++.h>
using namespace std;

int main() {
    char variableBefore = 'A';
    char array[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char variableAfter = 'B';

    cout << "Array[-1]: " << array[-1] << endl;
    cout << "Array[N]: " << array[10] << endl;
    cout << "Array[N+1]: " << array[11] << endl;

    cout << "Variable before array: " << variableBefore << endl;
    cout << "Variable after array: " << variableAfter << endl;
}

// B
#include<bits/stdc++.h>
using namespace std;

int main() {
    char variableBefore = 'A';
    char array[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char variableAfter = 'B';

    array[-1] = 'X';
    array[10] = 'Y';
    array[11] = 'Z';

    cout << "Variable before array (possibly changed): " << variableBefore << endl;
    cout << "Variable after array (possibly changed): " << variableAfter << endl;
}

// C
#include<bits/stdc++.h>
using namespace std;

int main() {
    char twoDimArray[3][4];

    for (int i = 0; i <= 5; ++i) {
        twoDimArray[0][i] = '0' + i;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << twoDimArray[i][j] << " ";
        }
        cout << endl;
    }
}