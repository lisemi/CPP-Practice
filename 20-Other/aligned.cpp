/*
提供用于存储联合类型和所需的大小的 POD 类型足够大，并适当对齐。
使用此模板类来获取的对齐方式和未初始化的存储中存储一个联合所需的大小。 
成员 typedef type 名称 POD 键入合适的存储中列出的任何类型的 Types; 最
小大小是 Len。 静态成员 alignment_value 类型的 std::size_t 包含中列出
的所有类型的所需的最严格的对齐方式 Types。
*/
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <type_traits>
using namespace std;

#if 1
#if defined __GNUC__ && __GNUC__ < 5 && !defined(_LIBCPP_VERSION)
constexpr std::size_t max(std::size_t a){
	return a;
}

constexpr std::size_t max(std::size_t a, std::size_t b){
	return a > b ? a : b;
}

template <typename... Vals>
constexpr std::size_t max(std::size_t a, std::size_t b, Vals... v){
	return max(a, max(b, v...));
}

// this is for backwards compatibility with not-quite C++11 compilers
// 用户实现C++11的aligned_union功能。
template <std::size_t Len, typename... Types>
struct aligned_union{
	struct type{
		alignas(max(alignof(Types)...))
		char buffer[max(Len, max(sizeof(Types)...))];
	};
};
#else
// Obtains a POD type suitable for use as storage for any object whose type is listed in Types, and a size of at least Len.
using std::aligned_union;
#endif
/*
union U_type {
	std::list<char> l;
	std::map<std::string, char> m;
	std::vector<int> v;
	int i;
	string s;
	U_type(string s) : s(s) {}
	//U_type(int i) : i(i) {}
};*/

int main() {
	aligned_union<1		// 最小分配空间
		, std::list<char>
		, std::map<std::string, char>
		, std::vector<int>
		, int
		, string
	>::type data;
	// placement new
	string* t = new(&data) string("hello");  // 如果没有定义U_type共用体，"U_type"直接替换成具体类型即可。如string("hello")
	std::cout << t << endl;		
	//std::cout << t->s << endl;	// 取值，需要定义一个共用体采用使用取值功能
	reinterpret_cast<string*>(&data)->~string(); //一定要析构，如果定义了共用体，对应的析构函数执行共用体具体类型变量，如: reinterpret_cast<string*>(&data)->~s
	cin.get();
	return 0;
}

#else
// 例2：
union U_type{
	int i;
	float f;
	double d;
	U_type(float e) : f(e) {}
};

typedef std::aligned_union<16, int, float, double>::type aligned_U_type;

int main(){
	// allocate memory for a U_type aligned on a 16-byte boundary
	aligned_U_type au;
	// do placement new in the aligned memory on the stack
	U_type* u = new (&au) U_type(1.0f);
	if (nullptr != u){
		std::cout << "value of u->i is " << u->i << std::endl;
		// must clean up placement objects manually!
		u->~U_type();
	}
	cin.get();
	return 0;
}
#endif