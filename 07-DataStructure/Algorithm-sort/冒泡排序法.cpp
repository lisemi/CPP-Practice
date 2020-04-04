/*
（无序区，有序区）。从无序区通过交换找出最大元素放到有序区前端。
选择排序思路：
1. 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
2. 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。
3. 针对所有的元素重复以上的步骤，除了最后一个。
4. 持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
时间复杂度：
平均时间复杂度：	O(n*n)
最差时间复杂度：	O(n*n)
空间复杂度：	 O(1)
数据对象稳定性： 稳定
*/
#include <iostream>
#include <vector>

using namespace std;

// 冒泡排序
// 该版本是小排最大值，排好的队列放到右边，因此右边会逐渐增长，左边会逐渐变短。
void BubbleSort(vector<int>& v) {
	int len = v.size();
	for (int i = 0; i < len - 1; ++i)
		for (int j = 0; j < len - 1 - i; ++j)
			if (v[j] > v[j + 1])
				swap(v[j], v[j + 1]);
}

// 模板实现冒泡排序
template<typename T> //整數或浮點數皆可使用,若要使用物件(class)時必須設定大於(>)的運算子功能
void bubble_sort(T arr[], int len) {
	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j < len - 1 - i; j++)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}

// 冒泡排序（改进版），这个版本针对队列里只有少量元素未排序的情况效率较高。
void BubbleSort_orderly(vector<int>& v) {
	int len = v.size();
	bool orderly = false;
	for (int i = 0; i < len - 1 && !orderly; ++i) {
		orderly = true;
		for (int j = 0; j < len - 1 - i; ++j) {
			if (v[j] > v[j + 1]) {  // 从小到大
				orderly = false;	// 发生交换则仍非有序
				swap(v[j], v[j + 1]);
			}
		}
	}
}

//#ifdef __cplusplus
//extern "C" {
#include <stdio.h>

	void swap(int arr[], int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	// 沉底法（从后到前，先找最小的）先排好小的数据。
	void bubbleSort_forc(int arr[], int len){ 
		for (int i = 0; i < len; i++) {
			for (int j = len - 1; j > i; j--)
				if (arr[j] < arr[j-1]) {
					swap(arr, j, j-1);
				}
		}
	}
	// 从前到后，先排好大的数据
	void preBubbleSort_forc(int arr[], int len) {
		for (int i = 0; i < len-1; i++) {
			for (int j = 0; j < len-i-1; j++)
				if (arr[j] > arr[j + 1]) {
					swap(arr, j, j + 1);
				}
		}
	}

	// 改进版本
	void bubbleSort_orderly_forc(int arr[], int len) {
		bool orderly = false;  // 是否已排序好，0：没有排好，1：排好了
		for (int i = 0; i < len && !orderly; i++) {
			orderly = true;
			for (int j = len - 1; j > i; j--)
				if (arr[j] < arr[j - 1]) {
					orderly = false;
					swap(arr, j, j - 1);
				}
		}
	}
//}
//#endif

int main13(int argc, char* argv[]) {
	int arr[] = {4,7,3,8,1};
	int len = sizeof(arr) / sizeof(arr[0]);
	preBubbleSort_forc(arr, len);
	for (int i = 0; i < len; i++)
		printf(" %d", arr[i]);
	printf("\n");

	getchar();
	return 0;
}