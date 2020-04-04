#include<iostream>
using namespace std;


class Base1 {
public:
	void fun() {
		cout << "I am base-1 " << endl;
	};
};

class Base2
{
public:
	void fun() {
		cout << "I am base-2 " << endl;
	};
};

class Subclass : public Base1, public Base2 {
public:
	void print() {
	}
};

int main() {
	Subclass obj;
	obj.Base1::fun();   //产生二歧义
	system("pause");
	return 0;
}