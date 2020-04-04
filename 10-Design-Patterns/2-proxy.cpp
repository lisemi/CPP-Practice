#include <iostream>
using namespace std;

class IFactory {
public:
	IFactory() {}
	virtual void makeProduct() = 0;
};

class PhoneFactory : public IFactory{
public:
	PhoneFactory() {}
	virtual void makeProduct(){
		cout << "生产手机" << endl;
	}
};

class FoxconnProxy : public IFactory{
public:
	FoxconnProxy(IFactory* factory){
		m_real = factory;
	}
	virtual void makeProduct(){
		highProduct();
		m_real->makeProduct();
	}
	void highProduct() {
		cout << "高速生成手机" << endl;
	}
private:
	IFactory* m_real;
};

int main(int argc, char* argv[]) {
	IFactory* factory = new PhoneFactory();
	FoxconnProxy* foxconn = new FoxconnProxy(factory);
	foxconn->makeProduct();
	cin.get();
	return 0;
}