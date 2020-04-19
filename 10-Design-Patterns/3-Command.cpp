#include <iostream>

using namespace std;

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

class Receiver{
public:
	void Action(){
		cout << "Receiver->Action" << endl;
	}
	void Cancel() {
		cout << "Cancel Action" << endl;
	}
};

class Command{
public:
	virtual void Execute() = 0;
	virtual void Cancel() = 0;
};

class ConcreteCommand : public Command{
public:
	ConcreteCommand(Receiver *pReceiver) : m_pReceiver(pReceiver) {}
	void Execute(){
		cout << "ConcreteCommand Send Command:" << endl;
		m_pReceiver->Action();
	}
	void Cancel() {
		cout << "ConcreteCommand Cancel Command:" << endl;
		m_pReceiver->Cancel();
	}
private:
	Receiver *m_pReceiver;
};


class Invoker{
public:
	Invoker(Command *pCommand) : m_pCommand(pCommand) {}
	void Invoke(){
		m_pCommand->Execute();
	}
	void CancelCommand() {
		m_pCommand->Cancel();
	}
private:
	Command *m_pCommand;
};

int main(){
	Receiver *pReceiver = new Receiver();
	Command *pCommand = new ConcreteCommand(pReceiver);
	Invoker *pInvoker = new Invoker(pCommand);

	pInvoker->Invoke();
	pInvoker->CancelCommand();

	SAFE_DELETE(pInvoker);
	SAFE_DELETE(pCommand);
	SAFE_DELETE(pReceiver);
	cin.get();
	return 0;
}

