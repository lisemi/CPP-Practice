#include <iostream>

class A{
public:

	void Func(void) { std::cout << "Func of class A" << std::endl; }
};

void Test(void){
	A *p;{
		A a;
		p = &a;  // 注意 a 的生命期
	}
	p->Func();   // p是“野指针", a在上面函数段已经释放，但编译器竟然是编译和运行通过的。可能是编译器做了某些工作
	system("pause");
}

int main(){
	Test();
}