#include <iostream>
using std::cout;
using std::endl;
using std::cin;

// 完成当前任务，需要把任务传递给下去
struct CarHandler {
public:
	virtual void HandlerCar() = 0;
	CarHandler* setNextHandler(CarHandler* handler) {
		m_handler = handler;
		return m_handler;
	}
protected:
	CarHandler* m_handler;
};

class HeadCarHandler : public CarHandler {
public:
	virtual void HandlerCar() {
		cout << "造车头" << endl;
		// 造完车头以后把任务传递给下一个执行者。
		if (m_handler != NULL) {
			m_handler->HandlerCar();
		}
	}
};
class BodyCarHandler : public CarHandler {
public:
	virtual void HandlerCar() {
		cout << "造车身" << endl;
		if (m_handler != NULL) {
			m_handler->HandlerCar();
		}
	}
};
class TailCarHandler : public CarHandler {
public:
	virtual void HandlerCar() {
		cout << "造车尾" << endl;
		if (m_handler != NULL) {
			m_handler->HandlerCar();
		}
	}
};

int main() {
	CarHandler* headHandle = new HeadCarHandler;
	CarHandler* bodyHandle = new BodyCarHandler;
	CarHandler* tailHandle = new TailCarHandler;
	// 业务顺序可以发生变化
	headHandle->setNextHandler(bodyHandle);
	bodyHandle->setNextHandler(tailHandle);
	tailHandle->setNextHandler(NULL);

	headHandle->HandlerCar();
	delete headHandle;
	delete bodyHandle;
	delete tailHandle;
	cin.get();
	return 0;
}