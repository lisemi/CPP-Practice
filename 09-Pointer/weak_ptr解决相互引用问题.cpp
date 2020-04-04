#include <iostream>
#include <memory>

class B;
class A{
public:
	A() {
		std::cout << "class A : constructor" << std::endl;
	}

	~A() {
		std::cout << "class A : destructor" << std::endl;
	}

	void referB(std::shared_ptr<B> test_ptr) {
		_B_Ptr = test_ptr;
	}
	void print_refer() {
		std::cout << "refer A count : " << _B_Ptr.use_count() << std::endl;
	}
	void test_refer() {
		std::shared_ptr<B> tem_p = _B_Ptr.lock();
		std::cout << "refer B : " << tem_p.use_count() << std::endl;
	}
private:
	std::weak_ptr<B> _B_Ptr;
};

class B{
public:
	B() {
		std::cout << "class B : constructor" << std::endl;
	}

	~B() {
		std::cout << "class B : destructor" << std::endl;
	}

	void referA(std::shared_ptr<A> test_ptr){
		_A_Ptr = test_ptr;
	}
	void print_refer() {
		std::cout << "refer A count : " << _A_Ptr.use_count() << std::endl;
	}
	void test_refer() {
		std::shared_ptr<A> tem_p = _A_Ptr.lock();
		std::cout << "refer A : " << tem_p.use_count() << std::endl;
	}

	std::weak_ptr<A> _A_Ptr;
};

int main(){
	// test
	{
		std::shared_ptr<A> ptr_a = std::make_shared<A>();   //A引用计算器为1
		std::shared_ptr<B> ptr_b = std::make_shared<B>();   //B引用计算器为1
		ptr_a->referB(ptr_b);  
		ptr_b->referA(ptr_a); 

		ptr_a->test_refer();
		ptr_b->test_refer();
		ptr_a->print_refer();
		ptr_b->print_refer();
	}
	system("pause");
	return 0;
}
