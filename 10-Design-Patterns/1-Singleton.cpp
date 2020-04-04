#include <iostream>
#include <mutex>
#if 1
// 懒汉式；即只有使用到的时候才去实例化，线程不安全，如多个线程同时执行时，并且
// 构造函数需要执行时间，就会导致多次执行构造函数，构造函数不安全，违背单例原则。
// 可以通过锁机制解决多线程安全问题。
class Singleton{
private:
	Singleton() { }
	static Singleton * pInstance;
public:
	static Singleton * GetInstance(){
		if (pInstance == nullptr)
			pInstance = new Singleton();
		return pInstance;
	}
	static void FreeInstance() {
		if (pInstance != NULL) {
			delete pInstance;
			pInstance = NULL;
		}
	}
};

// 线程安全懒汉式版本。
class Singleton {
private:
	Singleton() { }
	static Singleton * pInstance;
	static std::mutex mux;
public:
	static Singleton * GetInstance() {
		if (pInstance == nullptr) {
			std::lock_guard<std::mutex> lock{mux};
			pInstance = new Singleton();
		}
		return pInstance;
	}
	static void FreeInstance() {
		if (pInstance != NULL) {
			delete pInstance;
			pInstance = NULL;
		}
	}
};
#endif
// 线程安全的单例模式
class Singleton{
private:
	Singleton() { }
	~Singleton() { }
	Singleton(const Singleton &);
	Singleton & operator = (const Singleton &);
public:
	static Singleton & GetInstance(){
		static Singleton instance;
		return instance;
	}
	void print() {
		std::cout << "hello world" << std::endl;
	}
};

int main(int argc, char* argv[]) {
	Singleton& single = Singleton::GetInstance();

	single.print();
	std::cin.get();
	return 0;
}