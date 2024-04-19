#include <bits/stdc++.h>
using namespace std;

int main() {
    string string1, string2; 
    cin >> string1 >> string2;
    int count = 0;
    int length1 = string1.size();
    int length2 = string2.size();

    for (int i = 0; i <= length2 - length1; ++i) {
        const char* o = string1.c_str();
        const char* t = string2.c_str() + i;
        if (strncmp(t, o, length1) == 0) {
            ++count;
        }
    }
    cout << count << endl;
}
