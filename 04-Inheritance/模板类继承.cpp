#include <iostream>
#include <string>
using namespace std;

template <typename T>
class A {
public:
	A(T a) {
		m_a = a;
	}
	~A() {}

	void printA(){
		cout << "a : " << m_a << endl;
	}

private:
	T m_a;
};

// 普通类继承模板类
// 模板类派生时，需要具体化模板类，因为C++编译器需要知道父类的数据类型具体是什么，这样才知道分配多少内存。
class B : public A<int> {
public:
	B(const int a, const int b) :A<int>(a) {
		m_b = b;
	}
	void printB() {
		cout << "b : " << m_b << endl;
	}

private:
	int m_b;
};

// 模板类继承模板类。
template <typename T>
class C : public A<T> {
public:
	C(const int a, const int c) :A<T>(a) {
		m_c = c;
	}
	void printC() {
		cout << "c : "<< m_c << endl;
	}

private:
	T m_c;
};

int main(int argc, char* argv[]) {
	B b(1, 2);
	b.printA();
	b.printB();

	C<int> c(3, 4);
	c.printA();
	c.printC();
	cin.get();
}