/*
（有序区，无序区）。把无序区的第一个元素插入到有序区的合适的位置。对数组：比较得少，换得多。
插入排序思路：
1. 从第一个元素开始，该元素可以认为已经被排序
2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
4. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
5. 将新元素插入到该位置后
6. 重复步骤2~5

时间复杂度：
	平均时间复杂度：	O(n*n)
	最差时间复杂度：	O(n*n)
	空间复杂度：	 O(1)
	数据对象稳定性： 稳定
*/

#include <iostream>
#include <vector>

using namespace std;

// 插入排序
void InsertSort_forcpp(vector<int>& v)
{
	int len = v.size();
	for (int i = 1; i < len; ++i) {
		int temp = v[i];
		for (int j = i - 1; j >= 0; --j){
			if (v[j] > temp){
				v[j + 1] = v[j];
				v[j] = temp;
			}
			else
				break;
		}
	}
}

void InsertSort_forc(int arr[], int len)
{
	int temp = 0;

	for (int i = 1; i < len; ++i) {			// 第一个元素被认为是已经排好序
		temp = arr[i];						// 取出待排序的元素
		for (int j = i - 1; j >= 0; --j){	// 待排序的元素与已排好序的队列中取出的元素从后先前比较
			if (arr[j] > temp){				// 如果已排好序的某个元素大于待排序的原型，则已排好序的对应某个元素后移
				arr[j + 1] = arr[j];		// 元素后移
				arr[j] = temp;              // 元素插入
			}
			else
				break;
		}
	}
}

int main12(int argc, char* argv[]) {
	int arr[] = { 7,5,8,3,1,9 };
	printf("InsertSort_forc:\n");
	int len = sizeof(arr) / sizeof(arr[0]);
	InsertSort_forc(arr, sizeof(arr)/sizeof(arr[0]));
	for(int i=0; i<len; i++)
		printf(" %d", arr[i]);
	printf("\n");

	getchar();
	return 0;
}