#include <iostream>

int main() {
    char* a = new char[10];
    char* c = a + 3;

    for (int i = 0; i < 9; i++) a[i] = 'a';
    a[9] = '\0';

    std::cerr << "a: " << a << std::endl;
    std::cerr << "c: " << c << std::endl;

    delete c; // Sai: không nên dùng delete c; phải dùng delete[] a;

    std::cerr << "a after deleting c: " << a << std::endl;

    return 0;
}

#include <iostream>

int main() {
    char* a = new char[10];
    char* c = a + 3;

    for (int i = 0; i < 9; i++) a[i] = 'a';
    a[9] = '\0';

    std::cerr << "a: " << a << std::endl;
    std::cerr << "c: " << c << std::endl;

    delete[] a; // Đây là cách đúng để giải phóng bộ nhớ đã cấp phát cho a

    // Bất kỳ truy cập nào tới a hoặc c sau đây đều là không xác định và nguy hiểm
    // std::cerr << "a after deleting c: " << a << std::endl; // Dòng này sẽ bị comment lại vì nó không an toàn

    return 0;
}
