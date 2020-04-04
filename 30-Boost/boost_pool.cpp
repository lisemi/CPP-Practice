#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/timer/timer.hpp>

using namespace std;
using namespace boost;

const int MAXLENGTH = 100000;

class A{
public:
	A(){
		cout << "Construct: " << endl;
	}
	A(int a){
		cout << "Construct: " << a << endl;
	}
	~A(){
		cout << "Destruct" << endl;
	}
};

function<void(void) > pool_sample = [](){
	cout << "==============================\n";
	boost::object_pool<A> p;
	A *ptr = p.construct(1);
	p.destroy(ptr);
};

function<void(void) > pool_sample_1 = [](){
	cout << "==============================\n";
	boost::object_pool<A> p;
	A *ptr = p.malloc();
	cout << "malloc doesn't invoke constructor and destructor.\n";
	ptr = new (ptr) A(1);
	ptr->~A();
	p.free(ptr);
};


auto test_pool_alloc = [](){
	cout << "==============================\n";
	vector<int, pool_allocator<int>> vec1;
	vector<int> vec2;
	{
		cout << "USE pool_allocator:\n";
		boost::timer::auto_cpu_timer t;
		for (int i = 0; i < MAXLENGTH; ++i){
			vec1.push_back(i);
			vec1.pop_back();
		}
	}
	{
		cout << "USE STL allocator:\n";
		//boost::timer::auto_cpu_timer t2;
		for (int i = 0; i < MAXLENGTH; ++i)
		{
			vec2.push_back(i);
			vec2.pop_back();
		}
	}
};

auto test_fast_pool_alloc = [](){
	cout << "==============================\n";
	list<int, fast_pool_allocator<int>> vec1;
	list<int> vec2;
	{
		cout << "USE fast_pool_allocator:\n";
		//boost::timer::auto_cpu_timer t1;
		for (int i = 0; i < MAXLENGTH; ++i)
		{
			vec1.push_back(i);
			vec1.pop_back();
		}
	}
	{
		cout << "USE STL allocator:\n";
		//boost::timer::auto_cpu_timer t2;
		for (int i = 0; i < MAXLENGTH; ++i)
		{
			vec2.push_back(i);
			vec2.pop_back();
		}
	}
};

int main(){
	pool_sample();
	pool_sample_1();
	test_pool_alloc();
	test_fast_pool_alloc();
	system("pause");
}