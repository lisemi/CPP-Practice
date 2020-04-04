#include <iostream>

auto AddTest(int a, int b)
{
	return a + b;
}

int main()
{
	auto index = 10;
	auto str = "abc";
	auto ret = AddTest(1, 2);
	std::cout << "index:" << index << std::endl;
	std::cout << "str:" << str << std::endl;
	std::cout << "res:" << ret << std::endl;
	system("pause");
}
