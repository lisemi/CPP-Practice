#include <iostream>
#include <memory>

class B;
class A
{
public:
	A(){
		std::cout << "class A : constructor" << std::endl;
	}

	~A(){
		std::cout << "class A : destructor" << std::endl;
	}

	void referB(std::shared_ptr<B> test_ptr) {
		_B_Ptr = test_ptr;
	}
private:
	std::shared_ptr<B> _B_Ptr;
};

class B
{
public:
	B(){
		std::cout << "class B : constructor" << std::endl;
	}

	~B() {
		std::cout << "class B : destructor" << std::endl;
	}

	void referA(std::shared_ptr<A> test_ptr)
	{
		_A_Ptr = test_ptr;
	}

	std::shared_ptr<A> _A_Ptr; 
};


int main()
{
	// test
	{
		std::shared_ptr<A> ptr_a = std::make_shared<A>();   //A引用计算器为1
		std::shared_ptr<B> ptr_b = std::make_shared<B>();   //B引用计算器为1
		ptr_a->referB(ptr_b);   // B引用计算器加1
		ptr_b->referA(ptr_a);   // A引用计算器加1
	}
	system("pause");
	return 0;
}
