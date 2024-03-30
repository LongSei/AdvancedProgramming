#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> tconsume;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        tconsume.push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (tconsume[j] > tconsume[j + 1]) {
                swap(tconsume[j], tconsume[j + 1]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << tconsume[i] << " ";
    }
}