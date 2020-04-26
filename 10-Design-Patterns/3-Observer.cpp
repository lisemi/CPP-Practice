#include <iostream>
#include <string>
#include <list>

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
using namespace std;
class Secretary;
// 观察者
class PlayerObserver {
public:
	PlayerObserver(Secretary* secretary) :m_secretary(secretary) {}

	void update(string action) {
		cout << "action : " << action << endl;
	}
private:
	Secretary* m_secretary;
};
// 主题对象,被观察者
class Secretary {
public:
	Secretary() {
		m_list.clear();
	}
	void nodify(string action) {
		for (list<PlayerObserver*>::iterator it = m_list.begin(); it != m_list.end(); it++) {
			(*it)->update(action);
		}
	}
	void setPlayerObserver(PlayerObserver* o) {
		m_list.push_back(o);
	}

private:
	list<PlayerObserver*> m_list;
};
int main() {
	Secretary* secretary = NULL;
	PlayerObserver* po1 = NULL;
	PlayerObserver* po2 = NULL;
	secretary = new Secretary;
	po1 = new PlayerObserver(secretary);
	po2 = new PlayerObserver(secretary);
	secretary->setPlayerObserver(po1);
	secretary->setPlayerObserver(po2);
	secretary->nodify("请注意，老板来了");
	secretary->nodify("请放心，老板走了");
	SAFE_DELETE(po1);
	SAFE_DELETE(po2);
	SAFE_DELETE(secretary);
	std::cin.get();
	return 0;
}
