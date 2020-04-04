#include <iostream>
#include <algorithm>
using namespace std;

// 友元函数在类外面实现，并且都在同一个CPP文件中，需要在前面对类和对应操作符重载函数进行前置声明。
// 同时在类内部声明的对应函数需要在参数链表前加入 "<T>"。
template <typename T>
class Complex;           // 类前置声明
template <typename T>
Complex<T> operator++ (Complex<T> &c1, T);	// 函数前置声明

template <typename T>
class Complex{
public:
	Complex(T a = 0, T b = 0){
		this->a = a;
		this->b = b;
	}
	void print(){
		cout << a << " : " << b << endl;
	}
	//前置--
	Complex operator--(){
		Complex tmp = *this;
		this->a--;
		this->b--;
		return tmp;
	}
private:
	friend Complex<T> operator++ <T> (Complex<T> &c1, T);	// 后置需要增加一个占位
	friend ostream & operator<< <T> (ostream& out, Complex<T> &c2);

	T a;
	T b;
};

//后置++
template <typename T>
Complex<T> operator++(Complex<T> &c1, T){
	Complex<T> tmp = c1;
	c1.a++;
	c1.b++;
	return tmp;   // 由于是后置++，因此需要返回++前的对象
}

// "<<"和">>"由于函数重载，如果在同一个CPP里，但不在类内部实现，需要
// 在类内声明的时候在函数参数链表前加上"<T>"
template <typename T>
ostream & operator<< (ostream& out, Complex<T> &c2) {
	out << "a: " << c2.a << " b: " << c2.b << endl;
	return out;
}

void main(){
	Complex<int> c1(1, 2);

	// 友元函数重载运算符
	c1++;
	cout << c1 << endl;

	// 成员函数重载运算符
	--c1;
	cout << c1 << endl;
	cin.get();
	return;
}