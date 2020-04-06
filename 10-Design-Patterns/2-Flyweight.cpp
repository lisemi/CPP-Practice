#include <iostream>
#include <string>
#include <map>
using namespace std;

// 对应Flyweight
class Person {
public:
	Person(string name, int age) : m_name(name), m_age(age){}
	virtual void printT() = 0;
protected:
	string m_name;
	int m_age;
};
// 对应ConcreteFlyweight
class Teacher : public Person {
public:
	Teacher(string name, int age, string id) :Person(name, age), m_id(id) {}
	virtual void printT() {
		cout << "name:" << m_name << " age:" << m_age << " id:" << m_id << endl;
	}
private:
	string m_id;
};
// 对应FlyweightFactory
class FlyweightTeacherFactory {
public:
	FlyweightTeacherFactory() {
		m_map.clear();
	}
	~FlyweightTeacherFactory() {
		while (!m_map.empty()) {
			Person* tmp = NULL;
			map<string, Person*>::iterator it = m_map.begin();
			tmp = it->second;
			m_map.erase(it);
			delete tmp;
		}
	}
	Person* getTeacher(string id) {
		map<string, Person*>::iterator it = m_map.find(id);
		if (it == m_map.end()) {
			string t_name;
			int t_age = 0;
			cout << "input teacher name, please!" << endl;
			cin >> t_name;
			cout << "input teacher age, please!" << endl;
			cin >> t_age;
			Person* temp = new Teacher(t_name, t_age, id);
			m_map.insert(pair<string, Person*>(id, temp));
			return temp;
		}
		else {
			return it->second;
		}
	}
private:
	map<string, Person*> m_map;
};
int main(int argc, char* argv[]) {
	Person *p1 = NULL;
	Person *p2 = NULL;
	FlyweightTeacherFactory* fwtf = new FlyweightTeacherFactory;
	p1 = fwtf->getTeacher("001");
	p1->printT();

	p2 = fwtf->getTeacher("001");
	p2->printT();
	cin.get();
	return 0;
}