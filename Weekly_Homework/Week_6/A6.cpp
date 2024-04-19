#include<bits/stdc++.h>
using namespace std;

void f(int xval)
{
   int x;
   x = xval;
   cout << &x << endl;
}
void g(int yval)
{
   int y;
   cout << &y << endl;
}
int main()
{
   f(7);
   g(11);
   return 0;
} 

// Trong trường hợp của hai hàm f và g, vì cả hai hàm này liên tiếp nhau và không có hàm nào khác được gọi giữa chúng,
// Khi hàm f hoàn thành, khung ngăn xếp của nó được loại bỏ khỏi ngăn xếp, và khi hàm g sau đó được gọi, nó sử dụng lại cùng một vị trí trên ngăn xếp mà x đã từng chiếm giữ. 
// Do đó, địa chỉ của x và y có thể giống nhau