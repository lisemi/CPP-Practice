#pragma  once
#include <iostream>
using namespace std;

class Array{
public:
	Array(int length);
	Array(const Array& obj);
	~Array();

public:
	void setData(int index, int valude);
	int getData(int index);
	int length();

	//函数返回值当左值，需要返回一个引用(元素本身)
	int& operator[](int i);
	//重载=
	Array& operator=(Array &a1);
	//重载 ==
	bool operator==(Array &a1);
	//重载 !=
	bool operator!=(Array &a1);

private:
	int m_length;
	int *m_space;
};