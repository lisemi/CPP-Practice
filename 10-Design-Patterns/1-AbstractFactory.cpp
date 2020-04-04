#include <iostream>

using namespace std;

class Fruit {
public:
	virtual void sayName() = 0;
};
class AbstractFactory {
public:
	virtual Fruit* createBanana() = 0;
	virtual Fruit* createApple() = 0;
};

class NorthBanana : public Fruit {
public:
	virtual void sayName() {
		cout << "I'm north banama." << endl;
	}
};

class NorthApple : public Fruit {
public:
	virtual void sayName() {
		cout << "I'm north apple." << endl;
	}
};

class SouthBanana : public Fruit {
public:
	virtual void sayName() {
		cout << "I'm south banama." << endl;
	}
};

class SouthApple : public Fruit {
public:
	virtual void sayName() {
		cout << "I'm south apple." << endl;
	}
};

class NorthFactory : public AbstractFactory {
public:
	virtual Fruit* createBanana() {
		return new NorthBanana();
	}
	virtual Fruit* createApple() {
		return new NorthApple();
	}
};

class SouthFactory : public AbstractFactory {
public:
	virtual Fruit* createBanana() {
		return new SouthBanana();
	}
	virtual Fruit* createApple() {
		return new SouthApple();
	}
};

int main(int argc, char* argv[]) {
	Fruit* fruit = NULL;
	AbstractFactory* af = NULL;
	// 生产南方水果
	af = new SouthFactory();
	fruit = af->createApple();
	fruit->sayName();
	delete fruit;
	fruit = af->createBanana();
	fruit->sayName();
	delete fruit;
	// 生产北方水果
	af = new NorthFactory();
	fruit = af->createApple();
	fruit->sayName();
	delete fruit;
	fruit = af->createBanana();
	fruit->sayName();
	delete fruit;
	if (af != NULL) {
		delete af;
		af = NULL;
	}
	if (fruit != NULL) {
		delete fruit;
		fruit = NULL;
	}
	cin.get();
	return 0;
}