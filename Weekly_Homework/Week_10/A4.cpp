#include <iostream>
using namespace std;

int main() {
    int* ptr = new int(10); // Cấp phát bộ nhớ động cho một số nguyên và gán giá trị 10
    delete ptr;             // Giải phóng bộ nhớ đúng cách

    // Lỗi: Giải phóng bộ nhớ đã được giải phóng
    delete ptr;            
    return 0;
}
