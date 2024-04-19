#include <bits/stdc++.h>
using namespace std;

char* weird_string() {
    char c[] = "12345";
    return c;
}

int main() {
    char* str = weird_string();
    // Truy cập str ở đây có thể dẫn tới hành vi không xác định vì c đã không còn tồn tại nữa.
    cout << str << endl; // CẢNH BÁO: Hành vi không xác định!
    return 0;
}
