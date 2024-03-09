#include<bits/stdc++.h>
using namespace std;
set<string> st;
void BeautifulStrings(string s) {
    for (size_t i = 0; i < s.length(); ++i) {
        for (size_t j = i + 1; j < s.length(); ++j) {
            std::string temp = s;
            temp.erase(j, 1);
            temp.erase(i, 1); 
            st.insert(temp);
        }
    }
}

int main() {
    string inp;
    while (getline(cin, inp)) {
        BeautifulStrings(inp);
        cout << st.size() << endl;
        st = set<string>();
    }
}
