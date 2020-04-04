#include "myarray.h"

Array::Array(int length)
{
	if (length < 0){
		length = 0; 
	}
	m_length = length;
	m_space = new int[m_length];
}

//重写拷贝构造函数
Array::Array(const Array& obj){
	this->m_length = obj.m_length;
	this->m_space = new int[this->m_length]; 

	for (int i = 0; i<m_length; i++){
		this->m_space[i] = obj.m_space[i];
	}
}
Array::~Array(){
	if (m_space != NULL){
		delete[] m_space;
		m_space = NULL;
		m_length = -1;
	}
}

//a1.setData(i, i);
void Array::setData(int index, int valude){
	m_space[index] = valude;
}

int Array::getData(int index){
	return m_space[index];
}

int Array::length(){
	return m_length;
}

// a[i] = 1,因为要当左值使用，所以要返回引用
int& Array::operator[](int i){
	return m_space[i];
}

//a2 = a1;
Array& Array::operator=(Array &a1){
	if (this->m_space != NULL){
		delete[] m_space;
		m_length = 0;
	}
	m_length = a1.m_length;
	m_space = new int[m_length];

	for (int i = 0; i<m_length; i++){
		m_space[i] = a1[i];   // 因为已经重载了[]操作符
	}
	return *this;
}

//if (a3 == a1)
bool Array::operator==(Array &a1){
	if (this->m_length != a1.m_length){
		return false;
	}

	for (int i = 0; i<m_length; i++){
		if (this->m_space[i] != a1[i]){
			return false;
		}
	}
	return true;
}

bool Array::operator!=(Array &a1){
	return !(*this == a1);
}