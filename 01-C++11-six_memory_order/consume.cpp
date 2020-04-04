#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

/*
* x是个指针，依赖2个数据，int i=42, string s=”hello” , #3循环，直到#1 x被store，
* 那么在相应的依赖数据也设置好了，所以在#4,#5的断言也就可以通过。但a没有依赖，且是
* relaxed，不一定能判定断言
*/
struct X
{
	int i;
	std::string s;
};
std::atomic<X*> p;
std::atomic<int> a;
void create_x()
{
	X* x = new X;
	x->i = 42;
	x->s = "hello";
	//a.store(99, std::memory_order_relaxed);  // 
	p.store(x, std::memory_order_release);  // 1
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 手动模拟6判断不过的情况
	a.store(99, std::memory_order_relaxed); // 2
}
void use_x()
{
	X* x;
	while (!(x = p.load(std::memory_order_consume)))  // 3   等待1完成
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	assert(x->i == 42);  // 4
	assert(x->s == "hello");  // 5
	assert(a.load(std::memory_order_relaxed) == 99);  // 6
}
int main() {
	std::thread t1(create_x);
	std::thread t2(use_x);
	t1.join();
	t2.join();
}