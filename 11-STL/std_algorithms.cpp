#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

#include <iomanip> 
#include <numeric>
#include <queue>
#include <tuple>

using namespace std;

// 所有小于平均值的元素会被放在所有大于平均值的元素的后面
int partition(){
	std::vector<double> temperatures{ 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
	std::copy(std::begin(temperatures), std::end(temperatures), //List the values
		std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;

	auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0) / temperatures.size();
	std::cout << "Average temperature: " << average << std::endl;

	// 保持原来相对顺序
	std::stable_partition(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; });
	// 不保持原来相对顺序
	//std::partition(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; });

	std::copy(std::begin(temperatures), std::end(temperatures), std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;

	using gender = char;
	using monicker = string;
	using type= string;
	using Name = std::tuple<monicker, type, gender>;
	std::vector<Name> names{ std::make_tuple("Dan", "old", 'm'),std::make_tuple("Ann", "old", 'f'),std::make_tuple("Ed", "old",'m'),std::make_tuple("Jan", "old", 'f'), std::make_tuple("Edna", "old", 'f') };
	std::partition(std::begin(names), std::end(names), [](const Name name) { return std::get<2>(name) == 'f'; });

	for (const auto& name : names)
		std::cout << std::get<0>(name) << " " << std::get<1>(name) << " " << std::get<2>(name) << std::endl;

	// 返回true和false的元素分别放到不同的队列中
	// 方法一
	std::vector<double> low_t;                       // Stores below average temperatures
	std::vector<double> high_t;                      // Stores average or above temperatures
	std::partition_copy(std::begin(temperatures), std::end(temperatures), std::back_inserter(low_t), 
		std::back_inserter(high_t), [average](double t) { return t < average; });

	// Output below average temperatures
	std::cout << "below average:";
	std::copy(std::begin(low_t), std::end(low_t), std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;
	// Output average or above temperatures
	std::cout << "above average:";
	std::copy(std::begin(high_t), std::end(high_t), std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;

	// 方法二
	if (std::is_partitioned(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; })) // 序列是否已经被分区
	{
		// partition_point 获取第一个分区结束迭代器
		auto iter = std::partition_point(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; });
		std::cout << "Elements in the first partition: ";
		std::copy(std::begin(temperatures), iter, std::ostream_iterator<double>{std::cout, " " });
		std::cout << "\nElements in the second partition: ";
		std::copy(iter, std::end(temperatures), std::ostream_iterator<double>{std::cout, " "});
		std::cout << std::endl;
	}
	else
		std::cout << "Range is not partitioned." << std::endl;

	return 0;
}

/*
容器适配器是一个封装了序列容器的类模板，它在一般序列容器的基础上提供了一些不同的功能。
之所以称作适配器类，是因为它可以通过适配容器现有的接口来提供不同的功能。
stack<T>：是一个封装了 deque<T> 容器的适配器类模板，默认实现的是一个后入先出（Last-In-First-Out，LIFO）的压入栈
queue<T>：是一个封装了 deque<T> 容器的适配器类模板，默认实现的是一个先入先出（First-In-First-Out，LIFO）的队列。
priority_queue<T>：是一个封装了 vector<T> 容器的适配器类模板，默认实现的是一个会对元素排序，从而保证最大元素总在队列最前面的队列。
*/
int Container_adapter() {
	std::vector<double> numbers{ 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };

	// partial_sort
	std::partial_sort(std::begin(numbers), std::begin(numbers) + 5, std::end(numbers));
	std::cout << "partial_sort:";
	std::copy(std::begin(numbers), std::is_sorted_until(std::begin(numbers), std::end(numbers)), std::ostream_iterator<double>{std::cout, " " }); // 1.5 2.5 3.5 6 6.5 12
	std::cout << std::endl;

	// heap 创建堆
	std::make_heap(std::begin(numbers), std::end(numbers), std::greater<>());
	std::sort_heap(std::begin(numbers), std::end(numbers), std::greater<>());
	// Result: 12 10 8 6.5 6 3.5 2.5 1.5
	std::cout << "sort_heap:";
	for (auto vec : numbers) {
		std::cout << vec << " ";
	}
	std::cout << std::endl;

	// pop_heap() 函数将第一个元素移到最后，并保证剩下的元素仍然是一个堆，以后利用numbers.pop_back()删除最后一个元素
	std::pop_heap(std::begin(numbers), std::end(numbers), std::greater<>());
	// Result: 1.5 10 8 6.5 6 3.5 2.5 12
	std::cout << "pop_heap:";
	for (auto vec : numbers) {
		std::cout << vec << " ";
	}
	std::cout << std::endl;

	std::cout << "is_heap_until:";
	auto iter = std::is_heap_until(std::begin(numbers), std::end(numbers), std::greater<>());
	if (iter != std::end(numbers))
		std::cout << "numbers is a heap up to " << *iter << std::endl;


	// priority_queue； 定义了一个元素有序排列的队列。
	std::string wrds[]{ "one", "two", "three", "four" };
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> words2{ std::begin(wrds) , std::end(wrds) }; //"four" "one" "three" "two"
	std::cout << "priority_queue:";
	while (!words2.empty()) {
		std::cout << words2.top() << " ";
		words2.pop();
	}
	return 0;
}



int main()
{
	//partition();

	std::deque<string> song{ "jingle", "bells","jingle", "all", "the", "way" };
	song.resize(song.size() + 4); // Add 2 elements
	std::copy_backward(std::begin(song), std::begin(song) + 6, std::end(song));
	std::copy(std::begin(song), std::end(song), std::ostream_iterator <string> {std::cout, " "});
	std::cout << std::endl;

	system("pause");
	return 0;
}