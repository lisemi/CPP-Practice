#include <iostream>
#include <String>
using namespace std;

class  Student{
public:
	Student(const char *name, const int age){
		int _len = strlen(name);
		m_name = (char *)malloc(_len + 1); //
		strcpy_s(m_name, _len+1, name);
		m_age = age;
	}

	// Student obj2 = obj1;
	// 方法一：手工编写拷贝构造函数实现深copy
	Student(const Student& obj1){
		int _len = strlen(obj1.m_name);
		m_name = (char *)malloc(_len + 1);
		strcpy_s(m_name, _len+1, obj1.m_name);
		m_age = obj1.m_age;
	}

	// Student obj2 = obj1;  
	// 方法二：重载等号操作符实现深copy
	Student& operator=(Student &obj1){
		if (this->m_name != NULL){
			delete[] m_name;
			m_age = 0;
		}
		this->m_name = new char[strlen(obj1.m_name) + 1];
		strcpy_s(m_name, strlen(obj1.m_name)+1, obj1.m_name);
		this->m_age = obj1.m_age;
		return *this;
	}

	~Student(){
		if (m_name != NULL){
			free(m_name);
			m_name = NULL;
			m_age = 0;
		}
	}
protected:
private:
	char *m_name;
	int m_age;
};

//对象析构的时候 出现coredump
void test()
{
	Student obj1("xiaoming", 10);
	Student obj2 = obj1;          //调用用户实现的拷贝构造函数，实现深拷贝
	Student obj3("liming", 11);
	obj3 = obj1;        // 等号操作符
	obj1 = obj2 = obj3; // 需要返回引用
}

int main(){
	test();
	cout << "end..." << endl;
	system("pause");
	return 0;
}