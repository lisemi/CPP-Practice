#include <iostream>
using namespace std;

class Worker;

class State {
public:
	virtual void doSomeThing(Worker* w) = 0;
};

class Worker {
public:
	Worker();
	int getHour() {
		return m_hour;
	}
	void setHour(int hour) {
		m_hour = hour;
	}
	State* getCurrentState() {
		return m_currstate;
	}
	void setCurrentState(State* state) {
		m_currstate = state;
	}
	void doSomeThing() {
		m_currstate->doSomeThing(this);
	}
private:
	int m_hour;
	State* m_currstate;		// 对象的当前状态
};
class State1 : public State {
public:
	void doSomeThing(Worker* w);
};
class State2 : public State {
public:
	void doSomeThing(Worker* w);
};

void State1::doSomeThing(Worker* w) {
	if (w->getHour() == 7 || w->getHour() == 8) {
		cout << "7-8点：吃早餐" << endl;
	}
	else {  // 切换状态
		delete w->getCurrentState();
		w->setCurrentState(new State2);
		w->getCurrentState()->doSomeThing(w);
	}	
}

void State2::doSomeThing(Worker* w) {
	if (w->getHour() == 9 || w->getHour() == 10) {
		cout << "9-10点：工作" << endl;
	}
	else {
		delete w->getCurrentState();
		w->setCurrentState(new State1);
		w->getCurrentState()->doSomeThing(w);
		cout << "当前时间：" << w->getHour() << " 未知状态" << endl;
	}
}

Worker::Worker() {
	m_currstate = new State1;
}

int main() {
	Worker* worker = new Worker;
	worker->setHour(7);
	worker->doSomeThing();

	worker->setHour(9);
	worker->doSomeThing();
	delete worker;
	cin.get();
	return 0;
}