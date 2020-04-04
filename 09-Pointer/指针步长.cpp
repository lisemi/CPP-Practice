
#include <iostream>
using namespace std;

class Parent{
public:
	Parent(int a = 0){
		this->a = a;
	}

	virtual void print(){
		cout << "i am parent" << endl;
	}
private:
	int a;
};

class Child : public Parent{
public:
	Child(int b = 0) :Parent(0){
		this->b = b;
	}

	virtual void print(){
		cout << "i am child" << endl;
	}
private:
	int b;
};

void main(){
	Child  c1;
	Parent *pP = NULL;
	Child  *pC = NULL;
	Child  array[] = { Child(1), Child(2) };
	pP = array;
	pC = array;

	pP->print();
	pC->print(); 

	pP++;
	pC++;
	pP->print();
	pC->print();

	system("pause");
	return;
}