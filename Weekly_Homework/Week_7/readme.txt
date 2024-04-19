1. Cho đoạn lệnh sau:
Giả sử địa chỉ của c là 0x1234, địa chỉ của b là 0x5678. Hỏi output của đoạn lệnh sau là gì?

p3 = &d;
cout << "*p3 = " << *p3 << ", p3 = " << p3 << endl;
p3 = p1;
cout << "*p3 = " << *p3 << ", p3 = " << p3 << endl;
*p1 = *p2;
cout << "*p1 = " << *p1 << ", p1 = " << p1 << endl;

Output sẽ là:
*p3 = B, p3 = 0x5678
*p3 = A, p3 = 0x1234
*p1 = B, p1 = 0x1234

Giải thích:
- p3 được gán là địa chỉ của d, nên *p3 là 'B' và p3 là địa chỉ của d.
- Sau đó p3 được gán là p1, tức là *p3 và p3 lúc này sẽ là giá trị và địa chỉ của c.
- Cuối cùng, giá trị của *p1 được gán là *p2, tức là giá trị của c bây giờ là 'B'.

2. Cho các lệnh sau:
Các lệnh sau sẽ gán giá trị 5 cho i là:

*p = 5; // Vì p là con trỏ trỏ đến i, nên dòng này gán giá trị 5 cho i.
p = 5; // Đây là một lệnh gán không hợp lệ vì không thể gán giá trị số nguyên cho con trỏ.

3. Giải thích lỗi sau:
char c = 'C';
double *p = &c;

Lỗi ở đây là đang cố gắng gán địa chỉ của một biến kiểu char cho một con trỏ kiểu double.
Điều này không hợp lệ vì các kiểu char và double có kích thước khác nhau và con trỏ phải trỏ đến cùng kiểu dữ liệu mà nó được khai báo.