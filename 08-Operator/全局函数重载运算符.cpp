
#include <iostream>
using namespace std;

class Complex{
public:
	Complex(int a = 0, int b = 0){
		this->a = a;
		this->b = b;
	}
	void print(){
		cout << "a:b => " << a << ":" << b << endl;
	}
public:
	int a;
	int b;
};

Complex operator+(Complex &c1, Complex &c2){
	Complex tmp(c1.a + c2.a, c1.b + c2.b);
	return tmp; 
}

void main(){
	int a = 0, b = 0;
	int c = a + b; //1 基础类型编译器知道怎么做

	//用户定义复杂类型需要用户重载运算符编译才知道怎么做
	Complex c1(1, 2), c2(3, 4);
	Complex c3 = c1 + c2;
	c3.print();

	system("pause");
	return;
}