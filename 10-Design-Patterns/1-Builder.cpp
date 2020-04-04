#include <iostream>
#include <string>
using namespace std;

class House {
public:
	void setWall(string wall) {
		m_wall = wall;
	}
	void setDoor(string door) {
		m_door = door;
	}
	void setWindow(string window) {
		m_window = window;
	}
	string getWall() {
		cout << m_wall << endl;
		return m_wall;
	}
	string getDoor() {
		cout << m_door << endl;
		return m_door;
	}
	string getWindow() {
		cout << m_window << endl;
		return m_window;
	}
private:
	string m_wall;
	string m_door;
	string m_window;
};

class Builder {
public:
	virtual void buildWall() = 0;
	virtual void buildDoor() = 0;
	virtual void buildWindow() = 0;
	virtual House* getHouse() = 0;
};

class FlatBuilder : public Builder {
public:
	FlatBuilder() : house(new House) {}
	virtual void buildWall() {
		cout << "build flate wall" << endl;
		house->setWall("build flate wall");
	}
	virtual void buildDoor() {
		cout << "build flate door" << endl;
		house->setDoor("build flate door");
	}
	virtual void buildWindow() {
		cout << "build flate window" << endl;
		house->setWindow("build flate window");
	}
	virtual House* getHouse() {
		return house;
	}
private:
	House* house;
};

class VillaBuilder : public Builder {
public:
	VillaBuilder() : house(new House) {}
	virtual void buildWall() {
		cout << "build villa wall" << endl;
		house->setWall("build villa wall");
	}
	virtual void buildDoor() {
		cout << "build villa door" << endl;
		house->setDoor("build villa door");
	}
	virtual void buildWindow() {
		cout << "build villa window" << endl;
		house->setWindow("build villa window");
	}
	virtual House* getHouse() {
		return house;
	}
private:
	House* house;
};


class Director {
public:
	Director(Builder* build) : m_build(build) {}
	void construct() {
		m_build->buildWall();
		m_build->buildDoor();
		m_build->buildWindow();
	}
private:
	Builder* m_build;
};

int main(int argc, char* argv[]) {
	House* house = NULL;
	Builder* builder = NULL;
	Director* director = NULL;
	
	builder = new FlatBuilder;			// 请一个造公寓的工程队
	director = new Director(builder);	// 请一个指挥员指挥建公寓。
	director->construct();				// 指挥建公寓；
	house = builder->getHouse();		// 从工程队里拿公寓。
	delete house;
	delete builder;
	delete director;

	builder = new VillaBuilder;			// 请一个造别墅的工程队
	director = new Director(builder);	// 请一个指挥员指挥建别墅。
	director->construct();				// 指挥建别墅；
	house = builder->getHouse();		// 从工程队里拿别墅。

	if (house!=NULL) { delete house; house = NULL; }
	if (builder != NULL) { delete builder; builder = NULL; }
	if (director != NULL) { delete director; director = NULL; }
	cin.get();
	return 0;
}