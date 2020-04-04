#include <iostream>
#include <string>
#include <functional>

using namespace std;

int add(int a, int b){
	std::cout << "add" << std::endl;
	return a + b;
}

class Test{
public:
	void Add(std::function<int(int, int)> fun, int a, int b)
	{
		int sum = fun(a, b);
		std::cout << "sum:" << sum << std::endl;
	}
};

class TestAdd{
public:
	int Add(int a, int b){
		std::cout << "TestAdd::Add" << std::endl;
		return a + b;
	}
};

int main(){
	Test test;
	test.Add(add, 1, 2);

	//TestAdd testAdd;
	//test.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);
	return 0;
}
