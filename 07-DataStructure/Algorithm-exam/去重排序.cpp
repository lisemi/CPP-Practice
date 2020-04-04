/*
明明想在学校中请一些同学一起做一项问卷调查，为了实验的客观性，
他先用计算机生成了N个1到1000之间的随机整数（N≤1000），对于其
中重复的数字，只保留一个，把其余相同的数去掉，不同的数对应着不
同的学生的学号。然后再把这些数从小到大排序，按照排好的顺序去找
同学做调查。请你协助明明完成“去重”与“排序”的工作(同一个测试
用例里可能会有多组数据，希望大家能正确处理)。

Input Param
n               输入随机数的个数

inputArray      n个随机整数组成的数组

Return Value
OutputArray    输出处理后的随机整数

include< algorithm >
using std::random_shuffle;
random_shuffle(vi.begin(), vi.end()); // 打乱元素 

*/

// Generating a succession of 8 seeds
#include <random>                                // For random_device class
#include <iostream>                              // For standard streams
#include <set>
#include <algorithm>

using namespace std;
void print(const vector<int>& vc, const char* name) {
	cout << name << endl;
	for (int i = 0; i < vc.size(); i++)
		cout << " " << vc.at(i);
	cout << endl;
}

vector<int> getRom(int N) {
	vector<int> vc;
	if (N > 1000 || N < 1)
		return vc;
	std::random_device rd;
	while (N--) {
		vc.push_back(rd() % 10+1);
	}
	print(vc, "origin vector:");
	return vc;
}

void remove_duplic_v1(vector<int>& vc) {
	for (int i = 0; i < vc.size(); i++) {
		for (int j = 0; j < vc.size(); j++) {
			if (i == j)	continue;
			if (vc[i] == vc[j])
				vc.erase(vc.begin()+j);
		}
	}
	print(vc, "after remove duplicate :");
}

// 该版本只能针对已排序的队列进行去重。
// 因为unique删除相邻重复元素，因此需要先排序
void remove_duplic_v2(vector<int>& vc) {
	vc.erase(unique(vc.begin(), vc.end()), vc.end()); 
	print(vc, "after remove duplicate :");
}

// 该版本去重后会直接排好序
void remove_duplic_v3(vector<int>& vc) {
	set<int> s(vc.begin(), vc.end());
	vc.assign(s.begin(), s.end());
	print(vc, "after remove duplicate :");
}

void mysort(vector<int>& vc) {
	sort(vc.begin(), vc.end());
	print(vc, "after sort :");
}

int main()
{
	vector<int> vc = getRom(10);
	remove_duplic_v1(vc);
	mysort(vc);

	// stl查找算法
	vector<int> vcc;
	vcc.push_back(1);
	vcc.push_back(3);
	vcc.push_back(3);
	vcc.push_back(5);
	vcc.push_back(7);
	vcc.push_back(9);
	adjacent_find(vc.begin(), vc.end(), 3);		// 查找数组重复元素第一出现位置；
	binary_search(vc.begin(), vc.end(),7);		// 二分查找指定元素，返回是否成功bool值	，要去有序数列
	count(vc.begin(), vc.end(), 3);				// 查找元素个数
	//remove_duplic_v2(vc);
	cin.get();
}
