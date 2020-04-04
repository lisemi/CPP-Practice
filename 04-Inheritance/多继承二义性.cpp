
#include <iostream>
using namespace std;

class A{
public:
	int a;
};

class B1 : virtual public A{
public:
	int b1;
};

class B2 : virtual public A{
public:
	int b2;
};

class C : public B1, public B2{
public:
	int c1;
};

int main(){
	C  c1;
	c1.b1 = 100;
	c1.b2 = 200;
	c1.c1 = 300;

	c1.a = 500; //继承的二义性 和 虚继承解决方案

	cout << "end..." << endl;
	system("pause");
	return 0;
}