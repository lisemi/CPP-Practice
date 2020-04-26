#include <iostream>  
#include <string>
using namespace std;

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

/*中介类前置声明*/
class Mediator;

/*定义抽象人类，每个人都持有一个中介者的引用*/
class Person{
public:
	virtual void SetMediator(Mediator *mediator) = 0;
	virtual void SendMessage(string &message) = 0;
	virtual void GetMessage(string &message) = 0;
protected:
	Mediator *p_mediator; //中介    
};

/*定义抽象中介类*/
class Mediator{
public:
	virtual void Send(string &message, Person *person) = 0;
	virtual void SetRenter(Person *renter) = 0;
	virtual void SetLandlord(Person *landlord) = 0;
};

/*定义租客类*/
class Renter :public Person{
public:
	void SetMediator(Mediator *mediator) { p_mediator = mediator; }
	void SendMessage(string &message) { p_mediator->Send(message, this); }
	void GetMessage(string &message) { cout << "租房者收到房东发来的消息：" << message; }
};

/*定义房东类*/
class Landlord :public Person{
public:
	void SetMediator(Mediator *mediator) { p_mediator = mediator; }
	void SendMessage(string &message) { p_mediator->Send(message, this); }
	void GetMessage(string &message) { cout << "房东收到租客发来的消息：" << message; }
};

/*定义具体中介类 中介类需要持有关系方的对象。另外可以持有无数多个关系对象，可以使用列表的方式*/
class HouseMediator :public Mediator{
public:
	HouseMediator() :p_renter(NULL), p_landlord(NULL) {}
	void SetRenter(Person *renter) {
		p_renter = renter; 
	}
	void SetLandlord(Person *landlord) { 
		p_landlord = landlord; 
	}
	void Send(string &message, Person *person){   //接收消息的对象为该对象的对应对象
		if (person == p_renter)
			p_landlord->GetMessage(message);
		else
			p_renter->GetMessage(message);
	}
private:
	Person *p_renter;
	Person *p_landlord;
};
int main(int argc, char *argv[]){
	Mediator *mediator = new HouseMediator();
	Person *person1 = new Renter();
	Person *person2 = new Landlord();
	// 设置中介者的关系对象
	mediator->SetRenter(person1);
	mediator->SetLandlord(person2);
	// 设置person的的中介者
	person1->SetMediator(mediator);
	person2->SetMediator(mediator);
	// person通过中介者沟通
	person1->SendMessage(string("我想在深圳南山买套房子，三室一厅\n"));
	person2->SendMessage(string("我出售一套三室一厅房子，深圳南山\n"));
	SAFE_DELETE(person1);
	SAFE_DELETE(person2);
	SAFE_DELETE(mediator);
	cin.get();
	return 0;
}