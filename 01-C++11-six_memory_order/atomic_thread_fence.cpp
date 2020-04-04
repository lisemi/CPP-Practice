// 栅栏相当于给内存加了一层栅栏，约束内存乱序。典型用法是和 relaxed一起使用。
// 栅栏操作让无序变有序


// 栅栏#2同步与栅栏#5，所以 #1和#6就有了先行关系。 #7不会执行
#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;
void write_x_then_y()
{
	x.store(true, std::memory_order_relaxed);  // 1
	std::atomic_thread_fence(std::memory_order_release);  // 2
	y.store(true, std::memory_order_relaxed);  // 3
}
void read_y_then_x()
{
	while (!y.load(std::memory_order_relaxed));  // 4
	std::atomic_thread_fence(std::memory_order_acquire);  // 5
	if (x.load(std::memory_order_relaxed))  // 6
		++z;
}
int main() {
	x = false;
	y = false;
	z = 0;
	std::thread a(write_x_then_y);
	std::thread b(read_y_then_x);
	a.join();
	b.join();
	assert(z.load() != 0);  // 7
}