#include <iostream>
#include <list>
using namespace std;

class CompanyElement;

class Visitor {
public:
	virtual void visit(CompanyElement* cy) = 0;
};

class VisitorA : public Visitor {
public:
	void visit(CompanyElement* cy) {
		cout << "A部门管理者实现A部门的管理" << endl;
	}
};

class VisitorB : public Visitor {
public:
	void visit(CompanyElement* cy) {
		cout << "B部门管理者实现B部门的管理" << endl;
	}
};

// Element
class CompanyElement {
public:
	virtual void Accept(Visitor* visitor) = 0;
};

class RD_1 : public CompanyElement {
public:
	void Accept(Visitor* visitor) {
		cout << "RD_1: ";
		visitor->visit(this);   // RD_1部门接收管理者管理
	}
	void OperationA() {
		cout << "OperationA" << endl;
	}
};

class RD_2 : public CompanyElement {
public:
	void Accept(Visitor* visitor) {
		cout << "RD_2: ";
		visitor->visit(this);
	}
	void OperationB() {
		cout << "OperationB" << endl;
	}
};

class Company : public CompanyElement {
public:
	Company() {
		m_list.clear();
	}
	void setCompanyElement(CompanyElement* cyElement) {
		m_list.push_back(cyElement);
	}
	void Accept(Visitor* visitor) {
		for (list<CompanyElement*>::iterator it = m_list.begin(); it != m_list.end(); it++) {
			(*it)->Accept(visitor);   // 公司各个部分接收管理者管理；
		}
	}
private:
	list<CompanyElement*> m_list;
};

class ManagerVisitor : public Visitor {
public:
	void visit(CompanyElement* cy) {
		cout << "管理者管理公司的各个部分" << endl;
	}
};

int main1() {
	Visitor* vManager = new ManagerVisitor;
	Company* company = new Company;

	RD_1* rd1 = new RD_1;
	RD_2* rd2 = new RD_2;
	company->setCompanyElement(rd1);
	company->setCompanyElement(rd2);

	company->Accept(vManager);
	cin.get();
	return 0;
}