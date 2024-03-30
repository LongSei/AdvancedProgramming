#include<bits/stdc++.h>
using namespace std;
int checkPrime = 2;
int factorial(int x) {
    cout << "x = " << x << " at " << &x << endl;
    if (x == 1) {
        return 1;
    }
    return factorial(x - 1) * x;
}

int main() {
    int n = 10;
    cout << factorial(n);
}