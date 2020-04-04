#include <iostream>


int& g(){
	int a = 0;
	return a;
}

/* 若返回静态变量或者全局变量可以成为其他引用的初始值
*  即可以作为右值使用，也可以作为左值使用。
*/
int& h() {
	static int b = 0;
	return b;
}
#if 0
int main(){
	int a = g();
	int& b = g();
	int &c = h();  //地址给到c
	h() = 10;      //b的值改变，b的地址已经给了c，因此c的值也改变了
	printf("a = %d\n", a);
	printf("b = %d, b_addr = %x\n", b, &b);
	printf("c = %d\n", c);
	printf("f() = %d\n", h());
	system("pause");
	return 0;
}
#endif


#if 1
int main(){
	//int &x = 10; // 错误，因为10没有地址，引用是给地址其别名。
	const int &y = 10;	// 成功，编译器会单独给y分配一个地址。
	int a = 10;
	int &b = a;  //使用a初始化b引用，两者地址一样。注意：在C编译器会导致错误，没有引用。int * const b = &a 
	             //b是a的别名，请问c++编译器后面做了什么工作？
	b = 11;      //在C编译器会错误，没有定义 *b = 11;
	std::cout << "b--->" << a << std::endl;
	printf("a:%d\n", a);
	printf("b:%d\n", b);
	printf("&a:%d\n", &a);
	printf("&b:%d\n", &b);  //请思考：对同一内存空间可以取好几个名字吗？
	system("pause");
	return 0;
}
#endif

