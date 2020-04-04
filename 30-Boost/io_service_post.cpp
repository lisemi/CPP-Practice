#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <iostream>

using namespace boost::asio;
io_service service;
io_service::work g_work(service);

void func(int i) {
	std::cout << "func was called, i= " << i << std::endl;
}

void start() {
	service.run();
}

void stop() {
	service.stop();
}

int main(int argc, char* argv[]) {

	service.post(boost::bind(func, 10));
	boost::thread th(start);
	//start();   // 注意，直接在main函数启动无法实现work功能

	service.post(boost::bind(func, 11));   // 该语句可以运行，因为ioservice里的上一个任务还没运行完。

	// 如果没有io_service::work，以下代码不会运行。
	boost::this_thread::sleep(boost::posix_time::millisec(1000));
	for (int i = 0; i < 10; ++i)
		service.post(boost::bind(func, i));

	boost::this_thread::sleep(boost::posix_time::millisec(1000));
	for (int i = 100; i < 110; ++i)
		service.post(boost::bind(func, i));

	// wait for all threads to be created
	boost::this_thread::sleep(boost::posix_time::millisec(500));
	//th.join();
	system("pause");
	return 0;
}
