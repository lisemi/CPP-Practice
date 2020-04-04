#include <iostream>
using namespace std;

class test{
public:
	test() :a(0), b(0) {
	}
	~test() {
	}
	void add() {
		a++; b++;
		c++;   // 非静态函数可以使用静态成员变量
	}
	static void adds() {
		//a++; b++;  // 编译报错，静态成员函数无法使用非静态变量
		c++;
	}
	static int getC() {
		cout << "static c : " << c << endl;
		return c;
	}

	void print() {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
	}

private:
	int a;
	int b;
	static int c; //静态成员变量
};

class subTest:test {
public:
	void print() {
		cout << "subTest c:" << c << endl;
	}

private:
	static int c;
};

//静态类成员变量初始化
int test::c = 10;
int subTest::c = 100;

void main()
{

	test  a1, a2, a3;
	subTest b;
	a1.print(); //0,0,10
	a2.adds();  //0,0,12
	a2.add();   //1,1,12
	a3.print(); //0,0,12
	b.print();  // 100

	//静态成员函数的调用方法
	a3.getC();   //用对象.
	test::getC();  //类::

	cout << "end..." << endl;
	system("pause");
	return;
}
