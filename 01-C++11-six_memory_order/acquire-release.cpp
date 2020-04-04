//#define example_one
//#define example_two
//#define example_thr
#define example_four

#ifdef example_one
// 例1
#include <atomic>
#include <thread>
#include <assert.h>
std::atomic<bool> x, y;
std::atomic<int> z;
void write_x_then_y()
{
	x.store(true, std::memory_order_relaxed); // 1 自旋，等待y被设置为true
	y.store(true, std::memory_order_release);  // 2
}
void read_y_then_x()
{
	while (!y.load(std::memory_order_acquire));  // 3  等待2完成
	if (x.load(std::memory_order_relaxed))  // 4   一定可以判断成功
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
#endif

#ifdef example_two
// 例2
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<int> data[5];
std::atomic<bool> sync1(false), sync2(false);
void thread_1()
{
	data[0].store(42, std::memory_order_relaxed);
	data[1].store(97, std::memory_order_relaxed);
	data[2].store(17, std::memory_order_relaxed);
	data[3].store(-141, std::memory_order_relaxed);        
	data[4].store(2003, std::memory_order_relaxed);   
	sync1.store(true, std::memory_order_release); // 1.设置sync1 , 等待前面的写操作完成
}
void thread_2()
{
	while (!sync1.load(std::memory_order_acquire)); // 2.直到sync1设置后，循环结束
	sync2.store(true, std::memory_order_release);   // 3.设置sync2 
}
void thread_3()
{
	while (!sync2.load(std::memory_order_acquire)); // 4.直到sync2设置后，循环结束 
	assert(data[0].load(std::memory_order_relaxed)==42); 
	assert(data[1].load(std::memory_order_relaxed)==97); 
	assert(data[2].load(std::memory_order_relaxed)==17); 
	assert(data[3].load(std::memory_order_relaxed)==-141); 
	assert(data[4].load(std::memory_order_relaxed)==2003);
}

void main() {
	std::thread a(thread_1);
	std::thread b(thread_2);
	std::thread c(thread_3);
	a.join();
	b.join();
	c.join();
}

#endif

#ifdef example_thr
//例3
#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<int> sync(0);
void thread_1()
{
	// ...
	sync.store(1, std::memory_order_release);
}
void thread_2()
{
	int expected = 1;
	// 如果expected的值与sync的值相等，则把sync赋值为2，并执行memory_order_acq_rel
	while (!sync.compare_exchange_strong(expected, 2,
		std::memory_order_acq_rel)) //执行acquire-release 
		expected = 1;
}
void thread_3()
{
	while (sync.load(std::memory_order_acquire)<2);
	std::cout << "aync value : " << sync.load(std::memory_order_relaxed) << std::endl;
	// ...
}

void main() {
	std::thread a(thread_1);
	std::thread b(thread_2);
	std::thread c(thread_3);
	a.join();
	b.join();
	c.join();
}

#endif


#ifdef example_four
//例4
#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>
#include <vector>

std::vector<int> queue_data;
std::atomic<int> _count;

void populate_queue() {
	unsigned const number_of_items = 10;
	queue_data.clear();
	for (int i = 0; i < number_of_items; ++i) {
		queue_data.push_back(i);
	}
	_count.store(number_of_items, std::memory_order_release); // 1 初始化存储
}
void consume_queue_items()
{
	while (true)
	{
		int item_index;
		if (0 >= (item_index = _count.fetch_sub(1, std::memory_order_acquire))) // 2 一个“读-改-写”操作
		{
			//std::cout << std::this_thread::get_id() << ":wait for more items" << std::endl; // 3 等待更多元素
			continue;
		}
		std::cout << std::this_thread::get_id() << ": data=" << queue_data[item_index - 1] << std::endl; // 4 安全读取queue_data
	}
}
void play() {
	std::thread a(populate_queue);
	std::thread b(consume_queue_items);
	std::thread c(consume_queue_items);
	a.join();
	b.join();
	c.join();
}

void main() {
	play();
}
#endif