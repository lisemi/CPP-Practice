#include <iostream>
#include <string>
using namespace std;

class SubSystemA {
public:
	void doThing() {
		cout << "SubSystemA run." << endl;
	}
};

class SubSystemB {
public:
	void doThing() {
		cout << "SubSystemB run." << endl;
	}
};
// 装饰类，对其他功能类进行装饰。
class Facade {
public:
	Facade() {
		m_sysA = new SubSystemA;
		m_sysB = new SubSystemB;
	}
	~Facade() {
		if (m_sysA != NULL) delete m_sysA;
		if (m_sysB != NULL) delete m_sysB;
	}
	void doThing() {
		m_sysA->doThing();
		m_sysB->doThing();
	}
private:
	SubSystemA* m_sysA;
	SubSystemB* m_sysB;
};

int main(int argc, char* argv[]) {
	Facade* facade = new Facade;
	facade->doThing();
	delete facade;
	cin.get();
	return 0;
}