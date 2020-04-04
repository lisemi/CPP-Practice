#include <cstdlib>
#include <iostream>

using namespace std;

class Test{
public:
	Test(int i){
		this->m_a = i;
	}

	Test operator+ (const Test& obj){
		Test ret(0);

		ret.m_a = m_a + obj.m_a;
		return ret;
	}

	bool operator&& (const Test& obj){
		return m_a && obj.m_a;
	}
private:
	int m_a;
};

// && 从左向右
int main(){
	int a1 = 0;
	int a2 = 1;
	if (a1 && (a1 + a2)){
		cout << "a1,a2 结果为真..." << endl;
	}

	Test t1 = 0;
	Test t2 = 1;
	if(t1 && (t1 + t2)){
		cout << "t1,t2 结果为真..." << endl;
	}
	system("pause");
	return 0;
}
