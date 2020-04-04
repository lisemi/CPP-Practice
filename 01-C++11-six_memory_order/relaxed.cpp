/* C++11六大内存序介绍：
 * memory_order_relaxed：不对执行顺序做任何保证
 * memory_order_consume：本线程中，所有后续的有关本原子类型的操作，必须在本原子操作完成之后执行
 * memory_order_acquire：本线程中，所有后续的读操作必须在本条原子操作完成后执行
 * memory_order_release：本线程中，所有之前的写操作完成后才能执行本条原子操作
 * memory_order_acq_rel：同时包含 memory_order_acquire 和 memory_order_release的标记
 * memory_order_seq_cst：全部存取都按顺序执行
*/


// 没有顺序一致性的要求，也就是说同一个线程的原子操作还是按照happens-before关系，但不同线程间的执行关系是任意。
// 其中即使1先于2（同一个线程保证原子执行顺序）但是在不同线程间的执行顺序是没有约束的，所以#4也有可能是false 
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y()
{
	x.store(true, std::memory_order_relaxed);  // 1
	y.store(true, std::memory_order_relaxed);  // 2
}
void read_y_then_x()
{
	while (!y.load(std::memory_order_relaxed));  // 3
	if (x.load(std::memory_order_relaxed))  // 4
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
	assert(z.load() != 0);  // 5
}