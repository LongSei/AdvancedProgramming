#include <bits/stdc++.h>
using namespace std;

class String {
    private:
        char* str;

    public:
        String(const char* s) {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        }

        void print() const {
            cout << str;
        }

        void append(const char* s) {
            char* temp = new char[strlen(str) + strlen(s) + 1];
            strcpy(temp, str);
            strcat(temp, s);
            delete[] str;
            str = temp;
        }
};

int main() {
    String greeting("Hi");
    greeting.print(); 
    cout << endl;
    
    greeting.append(" there");
    greeting.print();
    cout << endl;
    
    return 0;
}
