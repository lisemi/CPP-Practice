/*
（有序区，无序区）。在无序区里找一个最小的元素跟在有序区的后面。对数组：比较得多，换得少。
选择排序思路：
1. 在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
2. 从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾
3. 以此类推，直到所有元素均排序完毕
时间复杂度：
	平均时间复杂度：	O(n*n)
	最差时间复杂度：	O(n*n)
	空间复杂度：		O(1)
	数据对象稳定性： 数组不稳定、链表稳定
*/

#include<iostream>
#include <vector>
#include <stdio.h>

using namespace std;

// 选择排序
void SelectionSort(vector<int>& v) {
	int min, len = v.size();
	for (int i = 0; i < len - 1; ++i) {
		min = i;        // 记住最小值的下标
		for (int j = i + 1; j < len; ++j) {  // 剩下的元素全部与min比较，小于min则记录下对应的下标，并把min的值改成对应的下标值，如此类推找出这次比较的最小值下标。
			if (v[j] < v[min]) {    // 标记最小的
				min = j;
			}
		}
		if (i != min)  // 小值交换到前面
			swap(v[i], v[min]);
	}
}

// 模板实现
template<typename T>
void Selection_Sort(std::vector<T>& arr) {
	int len = arr.size();
	for (int i = 0; i < len - 1; i++) {
		int min = i;
		for (int j = i + 1; j < len; j++)
			if (arr[j] < arr[min])
				min = j;
		if (i != min)
			std::swap(arr[i], arr[min]);
	}
}

#ifdef __cplusplus
extern "C" {
	void printf_arr(int arr[], int len) {
		for (int i = 0; i < len; i++)
			printf(" %d", arr[i]);
		printf("\n");
	}

	void swap(int arr[], int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	void selection_sort_c(int arr[], int len) {
		int i = 0;
		int j = 0;
		int min = 0;
		for (i = 0; i < len-1; i++) {   // 最后一次剩下一个数，不用在比较
			min = i;
			for (j = i + 1; j < len; j++) {
				if (arr[j] < arr[min])
					min = j;
			}
			if (i != min)
				swap(arr, i, min);
		}
	}
}
#endif

int main(int argc, char* argv[]) {
	
	int arr[] = { 4,6,3,7,2,1,8,5 };
	{
		int len = sizeof(arr) / sizeof(arr[0]);
		printf_arr(arr, len);
		selection_sort_c(arr, len);
		printf_arr(arr, len);
		getchar();
	}
/*
	{
		std::vector<int> vc;
		std::vector<int>::iterator it;
		it = vc.begin();
		vc.insert(it, arr, arr + 8);
		SelectionSort(vc);
		for (it = vc.begin(); it != vc.end(); it++)
			cout << " " << *it;
		cout << endl;
		cin.get();
	}
*/
	return 0;
}