#include <iostream>
using namespace std;
int curNumb = 0;
int prevNumb;
bool firstNumb = true;

void solve() {
    while (curNumb != -1) {
        cin >> curNumb;
        if (curNumb < 0) {
            cout << curNumb << " ";
            break;
        }
        if (firstNumb || curNumb != prevNumb) {
            cout << curNumb << " ";
            firstNumb = false;
        }
        prevNumb = curNumb;
    }
}

int main() {
    int test = 1;
    // cin >> test;
    while (test--) {
        solve();
    }
}
