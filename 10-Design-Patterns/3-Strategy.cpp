#include <iostream>
using std::cout;
using std::endl;

class Strategy {
public:
	virtual void Crypto() = 0;
};

class AES : public Strategy {
	virtual void Crypto() {
		cout << "AES加密算法" << endl;
	}
};

class DES : public Strategy {
	virtual void Crypto() {
		cout << "DES加密算法" << endl;
	}
};

class Context {
public:
	void setStrategy(Strategy* stratege) {
		m_strategy = stratege;
	}
	void myOperator() {
		m_strategy->Crypto();
	}
private:
	Strategy* m_strategy;
};

int main() {
	Strategy* strategy = NULL;
	strategy = new AES;
	Context* context = new Context;
	context->setStrategy(strategy);
	context->myOperator();
	std::cin.get();
	return 0;
}
