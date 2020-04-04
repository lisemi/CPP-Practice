#include <iostream>
using namespace std;

class Car {
public:
	Car() {}
	virtual void show() = 0;
};

class RunCar : public Car{
public:
	RunCar() {}
	virtual void show(){
		cout << "可以跑" << endl;
	}
};

class SwimRunCar : public Car{
public:
	SwimRunCar(Car* car){
		m_car = car;
	}
	void swim() {
		cout << "可以游" << endl;
	}
	virtual void show(){
		m_car->show();
		swim();
	}
private:
	Car* m_car;
};

class FlyRunCar : public Car {
public:
	FlyRunCar(Car* car) {
		m_car = car;
	}
	void fly() {
		cout << "可以飞" << endl;
	}
	virtual void show() {
		m_car->show();
		fly();
	}
private:
	Car* m_car;
};

int main(int argc, char* argv[]) {
	Car* car = NULL;
	car = new RunCar;
	car->show();
	SwimRunCar* swimRunCar = new SwimRunCar(car);
	swimRunCar->show();

	FlyRunCar* flyRunCar = new FlyRunCar(swimRunCar);
	flyRunCar->show();

	cin.get();
	return 0;
}