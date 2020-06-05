#include <iostream>
#include <list>
using namespace std;

typedef int Object;
#define SIZE 5
// 自定义抽象迭代器
class MyIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual Object CurrentItem() = 0;
};
// 抽象容器
class Aggregate {
public:
	virtual MyIterator* CreateIterator() = 0;  // 创建一个迭代器。
	virtual Object getItem(int index) = 0;
	virtual int getSize() = 0;
};
// 迭代器实现
class ConcreteIterator : public MyIterator {
public:
	ConcreteIterator(Aggregate* ag) {
		m_ag = ag;
		m_current_index = 0;
	}
	virtual void First() {
		m_current_index = 0;
	}
	virtual void Next() {
		if (m_current_index < m_ag->getSize()) {
			m_current_index++;
		}
	}
	virtual bool IsDone() {
		return (m_current_index == m_ag->getSize());
	}
	virtual Object CurrentItem() {
		return m_ag->getItem(m_current_index);
	}
private:
	int m_current_index;
	Aggregate* m_ag;
};

class ConcreteAggregate : public Aggregate {
public:
	ConcreteAggregate() {
		for (int i = 0; i < SIZE; i++) {
			m_object[i] = i + 100;
		}
	}
	MyIterator* CreateIterator() {
		return new ConcreteIterator(this);
	}
	Object getItem(int index) {
		return m_object[index];
	}
	int getSize() {
		return SIZE;
	}
private:
	Object m_object[SIZE];
};

int main() {
	Aggregate* ag = new ConcreteAggregate;
	MyIterator* it = ag->CreateIterator();
	for (; !(it->IsDone()); it->Next()) {
		cout << it->CurrentItem() << endl;
	}
	cin.get();
	return 0;
}