#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
	virtual void installEngine() = 0;
};

class Engine1100c  : public Engine {
public:
	virtual void installEngine() {
		cout << "I'm 1100c Engine, wellcome to use" << endl;
	}
};

class Engine4400c : public Engine {
public:
	virtual void installEngine() {
		cout << "I'm 4400c Engine, wellcome to use" << endl;
	}
};

class Car {
public:
	Car(Engine* engine) :m_engine(engine) {}
	virtual void installEngine() = 0;
protected:
	Engine* m_engine;
};

class BWM5 : public Car{
public:
	BWM5(Engine* engine) : Car(engine) { }
	virtual void installEngine() {
		cout << "I'm BWM5" << endl;
		m_engine->installEngine();
	}
};

class BWM7 : public Car {
public:
	BWM7(Engine* engine) : Car(engine) { }
	virtual void installEngine() {
		cout << "I'm BWM7" << endl;
		m_engine->installEngine();
	}
};
int main(int argc, char* argv[]) {
	Engine* engine = NULL; 
	Car* car = NULL;
	engine = new Engine1100c;
	car = new BWM5(engine);
	car->installEngine();
	delete engine;
	delete car;
	engine = new Engine4400c;
	car = new BWM7(engine);
	car->installEngine();

	cin.get();
	return 0;
}