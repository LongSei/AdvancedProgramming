#include <iostream>

int main() {
    int* p = new int;  // Cấp phát bộ nhớ cho một số nguyên
    int* p2 = p;       // p2 cũng trỏ đến cùng vùng bộ nhớ mà p trỏ đến

    *p = 10;           // Gán giá trị cho vùng bộ nhớ mà p trỏ đến
    delete p;          // Giải phóng bộ nhớ mà p trỏ đến

    *p2 = 100;         // Lỗi: p2 trỏ đến vùng bộ nhớ đã bị giải phóng

    std::cout << *p2;  // Lỗi: Cố gắng đọc từ vùng bộ nhớ đã bị giải phóng

    delete p2;         // Lỗi: Giải phóng bộ nhớ lần thứ hai, dẫn đến undefined behavior

    return 0;
}