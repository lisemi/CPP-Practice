#include <iostream>
using namespace std;

class Complex{
public:
	Complex(int a = 0, int b = 0){
		this->a = a;
		this->b = b;
	}
	void print(){
		cout << a << " : " << b << endl;
	}
public:
	//后置--
	Complex operator--(int){
		Complex tmp = *this;
		this->a--;
		this->b--;
		return tmp;
	}
private:
	int a;
	int b;
	friend Complex operator++(Complex &c1, int);
};

//后置++
Complex operator++(Complex &c1, int){
	Complex tmp = c1;
	c1.a++;
	c1.b++;
	return tmp;   // 由于是后置++，因此需要返回++前的对象
}

void main(){
	Complex c1(1, 2);

	// 友元函数重载运算符
	c1++;
	c1.print();

	// 友元函数重载运算符
	c1--;
	c1.print();

	system("pause");
	return;
}