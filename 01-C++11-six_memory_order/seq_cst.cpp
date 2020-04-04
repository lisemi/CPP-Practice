
// 全部安装顺序执行
#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>
std::atomic<bool> x, y;
std::atomic<int> z;
void write_x()
{
	x.store(true, std::memory_order_seq_cst);
	std::cout << "store x." << std::endl;
} // 1
void write_y()
{
	y.store(true, std::memory_order_seq_cst);
	std::cout << "store y." << std::endl;
}  // 2
void read_x_then_y()
{
	std::cout << "read_x_then_y: load x." << std::endl;
	while (!x.load(std::memory_order_seq_cst));
	std::cout << "read_x_then_y: load y." << std::endl;
	if (y.load(std::memory_order_seq_cst))  // 3
		++z;
}
void read_y_then_x()
{
	std::cout << "read_y_then_x: load y." << std::endl;
	while (!y.load(std::memory_order_seq_cst));
	std::cout << "read_y_then_x: load x." << std::endl;
	if (x.load(std::memory_order_seq_cst))  // 4
		++z;
}
int main() {
	x = false;
	y = false;
	z = 0;
	std::thread a(write_x);
	std::thread b(write_y);
	std::thread c(read_x_then_y);
	std::thread d(read_y_then_x);
	a.join();
	b.join();
	c.join();
	d.join();
	assert(z.load() != 0);  // 5 由于按照顺序执行，z肯定不为0
}