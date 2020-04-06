#include <iostream>
#include <string>

using namespace std;

class Current18v {
public:
	virtual void usrCurrent18v() = 0;
};

class Current220v {
public:
	void usrCurrent220v() {
		cout << "I'm 220v, Wellcom to use." << endl;
	}
};

class Adapter : public Current18v {
public:
	Adapter(Current220v* current) {
		m_current = current;
	}
	virtual void usrCurrent18v() {
		cout << "Adapter:  adaptive 18v to 220V" << endl;
		m_current->usrCurrent220v();
	}
private:
	Current220v* m_current;
};

int main(int argc, char* argv[]) {
	Current220v* current220v = new Current220v;
	Adapter* adapter = new Adapter(current220v);
	adapter->usrCurrent18v();   // we have 220v. but client use 18V
	delete current220v;
	delete adapter;
	cin.get();
	return 0;
}