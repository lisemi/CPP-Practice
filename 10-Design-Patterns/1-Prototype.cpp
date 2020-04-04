#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	virtual Person* clone() = 0;
	virtual void printT() = 0;
};

class CPPProgrammer : public Person {
public:
	CPPProgrammer() :m_name(""), m_age(0) {
		setResume("aa");
	}
	CPPProgrammer(string name, int age, char* resume) :m_name(name), m_age(age) {
		setResume(resume);
	}
	// 重载=实现深拷贝
	CPPProgrammer& operator=(const CPPProgrammer& p) {
		if (&p != this) {		// 防止自我赋值
			if (m_resume != NULL) {
				delete m_resume;
				m_resume = NULL;
			}
			m_name = p.m_name;
			m_age = p.m_age;
			m_resume = new char[strlen(p.m_resume) + 1];
			strcpy(m_resume, p.m_resume);
		}
		return *this;
	}
	void setResume(const char* resume) {
		if (m_resume != NULL) {
			delete m_resume;
		}
		m_resume = new char[strlen(resume) + 1];
		strcpy(m_resume, resume);
	}
	virtual void printT() {
		cout << "name : " << m_name << " age : " << m_age << " m_resume : " << m_resume << endl;
	}
	virtual Person* clone() {
		CPPProgrammer* tem = new CPPProgrammer;
		// 浅拷贝
		*tem = *this;
		// 深拷贝，因为重载=函数预防了自我赋值
		return tem;
	}

private:
	string m_name;
	int    m_age;
	char* m_resume;
};
int main(int argc, char* argv[]) {
	Person* p1 = new CPPProgrammer("张三", 18, "中国人");
	p1->printT();
	Person* p2 = p1->clone();
	p2->printT();

	cin.get();
	return 0;
}