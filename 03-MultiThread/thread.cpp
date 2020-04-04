#include <iostream>
#include <thread>

//使用例子
#if 0
void threadfun1()
{
	std::cout << "I am threadfun1" << std::endl;
}

void threadfun2(int iParam, std::string sParam)
{
	std::cout << "I am threadfun2 - para:" << iParam << std::endl;
}

int main()
{
	std::thread t1(threadfun1);
	std::thread t2(threadfun2, 10, "hello");
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	t1.join();
	std::cout << "t1 join" << std::endl;
	t2.detach();
	std::cout << "t2 detach" << std::endl;
	system("pause");
}


// 有问题例子
void thread1() {
	for (int i = 0; i<10; ++i)
		std::cout << "I am thread1..." << std::endl;
}

void thread2() {
	for (int i = 0; i<10; ++i)
		std::cout << "I am thread2..." << std::endl;
}

int main(int argc, char* argv[]) {
	std::thread th1(thread1); // 实例化线程对象
	std::thread th2(thread2);
	std::cout << "out : main..." << std::endl;
	return 0;
}


// join例子
void thread1() {
	for (int i = 0; i<10; ++i)
		std::cout << "thread1..." << std::endl;
}

void thread2() {
	for (int i = 0; i<10; ++i)
		std::cout << "thread2..." << std::endl;
}

int main(int argc, char* argv[]) {
	std::thread th1(thread1);   // 实例化线程对象
	std::thread th2(thread2);
	std::cout << "th1->1 status : " << th1.joinable() << std::endl;
	th1.join();
	std::cout << "th1->2 status : " << th1.joinable() << std::endl;
	th2.join();
	std::cout << "out : main..." << std::endl;
	system("pause");
	return 0;
}

// detach例子
void thread1() {
	for (int i = 0; i<10; ++i)
		std::cout << "thread1..." << std::endl;
}

void thread2() {
	for (int i = 0; i<10; ++i)
		std::cout << "thread2..." << std::endl;
}

int main(int argc, char* argv[]) {
	std::thread th1(thread1);   // 实例化线程对象
	std::thread th2(thread2);
	th1.detach();
	th2.detach();
	std::cout << "out : main..." << std::endl;
	system("pause");
	return 0;
}



// 线程互斥：mutex，线程不安全锁
#include<mutex>

std::mutex m;
int cnt = 15;

void thread1() {
	m.lock();
	for(; cnt>10; cnt--)
		std::cout << "thread1: cnt=" << cnt << std::endl;
	//return;     // 手动制作线程异常
	m.unlock();
}

void thread2() {
	m.lock();
	cnt -= 10;
	std::cout << "thread2: cnt=" << cnt << std::endl;
	m.unlock();
}

int main(int argc, char* argv[]) {
	std::thread th1(thread1);   
	std::thread th2(thread2);
	th1.join();
	th2.join();
	std::cout << "out : main..." << std::endl;
	system("pause");
	return 0;
}
#endif

//线程互斥：lock_guard，线程安全锁
#include<mutex>

std::mutex m;
int cnt = 15;

void thread1() {
	std::lock_guard<std::mutex> lock(m);
	for (; cnt>10; cnt--)
		std::cout << "thread1: cnt=" << cnt << std::endl;
	return;     // 手动制作线程异常
}

void thread2() {
	std::lock_guard<std::mutex> lock(m);
	cnt -= 10;
	std::cout << "thread2: cnt=" << cnt << std::endl;
}

int main(int argc, char* argv[]) {
	std::thread th1(thread1);
	std::thread th2(thread2);
	th1.join();
	th2.join();
	std::cout << "out : main..." << std::endl;
	system("pause");
	return 0;
}