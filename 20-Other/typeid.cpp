#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <deque>
/*
* sbstract:
* typeid是C++的关键字之一，等同于sizeof这类的操作符。typeid操作符的返回结果是名为type_info的标准库类型的对象的
* 引用（在头文件typeinfo中定义，稍后我们看一下vs和gcc库里面的源码）.如果表达式的类型是类类型且至少包含有一个虚
* 函数，则typeid操作符返回表达式的动态类型，需要在运行时计算；否则，typeid操作符返回表达式的静态类型，在编译时
* 就可以计算。
* t.name()	 返回类型的C-style字符串，类型名字用系统相关的方法产生
* t1.before(t2)	 返回指出t1是否出现在t2之前的bool值
*/
#include <map>
#include <array>
using namespace std;

struct Base {}; // 非多态
struct Derived : Base {};

struct Base2 { virtual void foo() {} }; // 多态
struct Derived2 : Base2 {};
#if 0 
int main(int argc, char* argv[]) {
	int myint = 50;
	std::string mystr = "string";
	double *mydoubleptr = nullptr;

	std::cout << "myint has type: " << typeid(myint).name() << '\n'
		<< "mystr has type: " << typeid(mystr).name() << '\n'
		<< "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n';

	// std::cout << myint 为多态类型的泛左值表达式；求值
	const std::type_info& r1 = typeid(std::cout << myint);
	std::cout << '\n' << "std::cout<<myint has type : " << r1.name() << '\n';

	// std::printf() 不是多态类型的泛左值表达式；不求值
	const std::type_info& r2 = typeid(std::printf("%d\n", myint));
	std::cout << "printf(\"%d\\n\",myint) has type : " << r2.name() << '\n';

	// 非多态左值时为静态类型
	Derived d1;
	Base& b1 = d1;
	std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';

	Derived2 d2;
	Base2& b2 = d2;
	std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';

	try {
		// 解引用空指针：对于非多态表达式 OK
		std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n';
		// 解引用空指针：对多态左值则不行
		Derived2* bad_ptr = nullptr;
		std::cout << "bad_ptr points to... ";
		std::cout << typeid(*bad_ptr).name() << '\n';
	}
	catch (const std::bad_typeid& e) {
		std::cout << " caught " << e.what() << '\n';
	}
	int a[] = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> vc;
	std::list<int> l;
	std::deque<int> dq;
	std::map<int, string> m;
	array<int, 10> ay;
	vc.assign(a, a + 9);
	m.insert(pair<int, string>(1, "abc"));
	std::cin.get();
	return 0;
}
#endif

int main() {
	int arr[] = { 1,2,3,4,5,6 };
	vector<int> vec(arr, arr + 6);
	vector<int>::iterator it = vec.begin();
	advance(it, 3);  // it迭代器补进3步，其不检查迭代器是否超过序列的end()。
	copy(arr, arr + 3, it);
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ","));
	cout << endl;
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ","));
	cout << endl;
	copy(arr + 3, arr + 6, inserter(vec, it));
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ","));
	typedef std::list<int>::iterator lit;
	typeid(typename std::iterator_traits<lit>::iterator_category) == typeid(std::random_access_iterator_tag);
	cin.get();
	return 0;
}
