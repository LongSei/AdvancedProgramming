#include<bits/stdc++.h>
using namespace std;

char* concat(const char* a, const char* b) {
    char* result = new char[strlen(a) + strlen(b) + 1];
    strcpy(result, a);
    strcat(result, b);
    return result;
}

int main() {
    const char* string1 = "Hello";
    const char* string2 = "World";

    char* combinedString = concat(string1, string2);
    cout << combinedString << endl;
    delete[] combinedString;

    return 0;
}
