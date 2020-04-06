/*
（小数，基准元素，大数）。在区间中随机挑选一个元素作基准，将小于基准的元素放在基准之前，
大于基准的元素放在基准之后，再分别对小数区与大数区进行排序。
快速排序思路：
1. 选取第一个数为基准
2. 将比基准小的数交换到前面，比基准大的数交换到后面
3. 对左右区间重复第1、2步，直到各区间只有一个数

该方法是在冒泡方法的基础上改进而得。
时间复杂度：
	平均时间复杂度：	O(n*log2n)（2是底数，不是2*n）
	最差时间复杂度：	O(n*n) （2是底数，不是2*n）
	空间复杂度：		O(log2n) （2是底数，不是2*n）	
	数据对象稳定性： 不稳定；例如有两个连续一样的元素，并且选择了其中一个座位pivot因子。
*/
#include <iostream>
#include <vector>
using namespace std;

// 快速排序（递归）
void QuickSort(vector<int>& v, int low, int high) {
	if (low >= high)		// 结束标志
		return;
	int first = low;		// 低位下标
	int last = high;		// 高位下标
	int key = v[first];		// 设第一个为基准

	while (first < last)
	{
		// 将比第一个小的移到前面
		while (first < last && v[last] >= key)
			last--;
		if (first < last)
			v[first++] = v[last];   // 首先会把v[last]赋给v[first]，然后first再自加，因为++游标量后面。将比key小的移到原来拿key对应下标的位置（即v[first]），然后再右移左游标

		// 将比第一个大的移到后面
		while (first < last && v[first] <= key)
			first++;
		if (first < last)
			v[last--] = v[first];   // 到此完成一轮小左大右交换
	}
	// 基准置位，基准下标位置为key所在的位置，每次递归进来这个下标都会变
	v[first] = key;
	// 前半递归
	QuickSort(v, low, first - 1);
	// 后半递归
	QuickSort(v, first + 1, high);
}

void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int Partition(int arr[], int low, int high) {
	int key = arr[low];
	// 左右子序交替查找值与key比较。
	while (low < high) {
		while (low < high && arr[high] >= key) // 如果大于key值，high游标左移
			high--;
		swap(arr, low, high);                  // 否则把该值（arr[high]）移到low下标处，此时arr[high]位置则作为左子序low游标找到大于key值的值的存放位置。
		while (low < high && arr[low] <= key)  // 如果小于key值，low游标右移
			low++;
		swap(arr, low, high);
	}
	return low;
}

void QSort(int arr[], int low, int high) {
	if (low < high) {
		// 选择一个key（当初是第一个），排小于和大于key的数值放在左右两边，并把pivot位置带回来。
		int pivot = Partition(arr, low, high);
		// 对左子序排序
		QSort(arr, low, pivot-1);
		// 对右子序排序
		QSort(arr, pivot + 1, high);
	}
}

// ----------------------------------------------------

// 模板实现快速排序（递归）
template <typename T>
void quick_sort_recursive(T arr[], int start, int end) {
	if (start >= end)
		return;
	T mid = arr[end];
	int left = start, right = end - 1;
	while (left < right) {
		while (arr[left] < mid && left < right)
			left++;
		while (arr[right] >= mid && left < right)
			right--;
		std::swap(arr[left], arr[right]);
	}
	if (arr[left] >= arr[end])
		std::swap(arr[left], arr[end]);
	else
		left++;
	quick_sort_recursive(arr, start, left - 1);
	quick_sort_recursive(arr, left + 1, end);
}
template <typename T> //整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort(T arr[], int len) {
	quick_sort_recursive(arr, 0, len - 1);
}

// ----------------------------------------------------

// 模板实现快速排序（迭代）
struct Range {
	int start, end;
	Range(int s = 0, int e = 0) {
		start = s, end = e;
	}
};
template <typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort_iterator(T arr[], const int len) {
	if (len <= 0)
		return; // 避免len等於負值時宣告堆疊陣列當機
				// r[]模擬堆疊,p為數量,r[p++]為push,r[--p]為pop且取得元素
	Range r[len];
	int p = 0;
	r[p++] = Range(0, len - 1);
	while (p) {
		Range range = r[--p];
		if (range.start >= range.end)
			continue;
		T mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right) left++;
			while (arr[right] >= mid && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[range.end])
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Range(range.start, left - 1);
		r[p++] = Range(left + 1, range.end);
	}
}

int main(int arvc, char* argv[]) {
	int arr[] = {4,9,2,5,3,33};
	int len = sizeof(arr) / sizeof(arr[0]);
	vector<int> vc;
	vc.insert(vc.begin(), arr, arr + 6);
	QSort(arr, 0, len-1);
	for (int i = 0; i < len; i++)
		printf(" %d", arr[i]);
	printf("\n");
	/*
	vector<int>::iterator it;
	for (it = vc.begin(); it != vc.end(); it++)
		cout << " " << *it;
	cout << endl;
	*/

	cin.get();

	return 0;
}