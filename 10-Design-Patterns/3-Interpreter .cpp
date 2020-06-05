#include <iostream>
using namespace std;

// 解释器使用的一些全局信息
class Context {
public:
	Context(int num) {
		m_num = num;
	}
	int getNum() {
		return m_num;
	}
	int getRes() {
		return m_res;
	}
	void setNum(int num) {
		m_num = num;
	}
	void setRes(int res) {
		m_res = res;
	}
private:
	int m_num;
	int m_res;
};

class Expression {
public:
	virtual void interpreter(Context* context) = 0;

private:
	Context* m_context;
};
// 加法解释器
class PlusExpression : public Expression {
public:
	PlusExpression() {
		m_context = NULL;
	}
	void interpreter(Context* context) {
		int num = context->getNum();
		num++;
		context->setNum(num);
		context->setRes(num);
	}
private:
	Context* m_context;
};
// 减法解释器
class MinusExpression : public Expression {
public:
	MinusExpression() {
		m_context = NULL;
	}
	void interpreter(Context* context) {
		int num = context->getNum();
		num--;
		context->setNum(num);
		context->setRes(num);
	}
private:
	Context* m_context;
};

int main() {
	Context* context = new Context(10);
	Expression*  expn1 = new PlusExpression;
	expn1->interpreter(context);
	cout << context->getNum() << endl;
	Expression* expn2 = new MinusExpression;
	expn2->interpreter(context);
	cout << context->getNum() << endl;
	cin.get();
	return 0;
}