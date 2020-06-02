/* 本实例介绍C++各种new的使用方法 */
#include <iostream>

void outOfMem() {
	std::cout << "unable to satisfy request for memory." << std::endl;
	std::abort();
}

//namespace std {
//	typedef void(*new_handler)();
//	new_handler set_new_handler(new_handler p) throw();
//}

class Base {
public:
	// normal new/delete
	static void* operator new(std::size_t size) throw(std::bad_alloc) {
		return ::operator new(size);
	}
	static void operator delete(void* pMemory) throw() {
		::operator delete(pMemory);
	}
	// placement new/delete; 用于在给定的内存中初始化对象,这种new允许在一块已经分配成功的内存上重新构造对象或对象数组。	
	static void* operator new(std::size_t size, void* ptr) throw() {
		return ::operator new(size, ptr);
	}
	static void operator delete(void* pMemory, void* ptr) throw() {
		::operator delete(pMemory, ptr);
	}
	// nothrow new/delete; 不抛出异常的运算符new的形式
	static void* operator new(std::size_t size, const std::nothrow_t& nt) throw() {
		return ::operator new(size, nt);
	}
	static void operator delete(void* pMemory, const std::nothrow_t& nt) throw() {
		::operator delete(pMemory);
	}
	// custom placement new/delete
	static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {
		return ::operator new(size);
	}
	static void operator delete(void* pMemory, std::ostream& logStream) throw() {
		::operator delete(pMemory);
	}
};

int main() {
	// call normal new
	Base* base1 = new Base;		
	delete base1;
	// call placement new
	int p[1024];		// 可以是其他，如void* p = new sizeof(Base);
	Base* base2 = new (p) Base;	
	base2->Base::~Base();				// 需要手动析构
	// call nothrow new
	Base* base3 = new (std::nothrow) Base;	
	delete base3;
	// call custom placement new
	Base* base4 = new (std::cerr) Base;	
	delete base4;
	// memory leak test.
	std::set_new_handler(outOfMem);
	int* bigMem = new int[100000000L];
	std::cin.get();
	return 0;
}
