// Cho hàm cube sau:
		void cube(int i) { 
		   i = i * i * i; 
		}
// Hỏi trong vòng lặp sau, hàm cube() chạy bao nhiêu lần?
for (int i = 0; i < 1000; i++) 
	   cube(i);

// cube sẽ được chạy 1000 lần