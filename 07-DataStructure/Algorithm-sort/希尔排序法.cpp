/*
希尔排序：每一轮按照事先决定的间隔进行插入排序，间隔会依次缩小，最后一次一定要是1。
希尔排序法是在插入法的基础上增加分组的功能，是业界第一个突破O(n*n)时间复杂度的算法
分组数量经验公式：
	num = len/3 +1
时间复杂度：
	平均时间复杂度：	O(n*n)
	最差时间复杂度：	O(n*n)
	空间复杂度：	 O(1)
	数据对象稳定性： 数组不稳定、链表稳定
*/

#include <iostream>

template<typename T>
void shell_sort(T array[], int length) {
	int h = 1;
	while (h < length / 3) {  // 计算间隔距离
		h = 3 * h + 1;
	}
	while (h >= 1) {
		for (int i = h; i < length; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {  // 如果这组数据前面的大于后面的，则交换。
				std::swap(array[j], array[j - h]);
			}
		}
		h = h / 3;  // 间隔距离不断减小
	}
}

int main11(int argc, char* argv[]) {
	int arr[] = {3,6,1,5,9};
	int len = sizeof(arr) / sizeof(arr[0]);
	shell_sort<int>(arr, len);
	for (int i = 0; i < len; i++)
		std::cout << " " << arr[i];
	std::cout << std::endl;

	std::cin.get();
	return 0;
}