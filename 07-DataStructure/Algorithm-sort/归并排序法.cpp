/*
归并排序：把数据分为两段，从两段中逐个选最小的元素移入新数据段的末尾。可从上到下或从下到上进行。
首先进行两路多分工程，最后进行归并（前没划分成多少路就归并多少路）。
对一个数据分成两路，min中间。合拼过程：
	1）设置i、j和k三个指针，其初值分别指向这三个记录区的起始位置；
	2）合并时依次比较R[i]和R[j]的关键字，取关键字较小的记录复制到R1[k]中；
	3）然后将被复制记录的指针i或j加1，以及指向复制位置地指针k加1；
	4）重复这一过程直至两个输入的子文件有一个已全部复制完毕，此时将另一个非空的子文件中剩余的记录依次复制到R1中即可。
时间复杂度：
	平均时间复杂度：	O(n*log2n)（2是底数，不是2*n）
	最差时间复杂度：	O(n*log2n)（2是底数，不是2*n）
	空间复杂度：		O(n)
	数据对象稳定性： 稳定
*/
#include <iostream>

/*****************
迭代版
*****************/
//整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
template<typename T>
void merge_sort_iterator(T arr[], int len) {
	T* a = arr;
	T* b = new T[len];
	for (int seg = 1; seg < len; seg += seg) {
		for (int start = 0; start < len; start += seg + seg) {
			int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		T* temp = a;
		a = b;
		b = temp;
	}
	if (a != arr) {
		for (int i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
	}
	delete[] b;
}

/*****************
递归版
*****************/
template<typename T>
void merge_sort_recursive(T arr[], T reg[], int start, int end) {
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;   // 求数组长度，以及前后子序的分割点
	int start1 = start, end1 = mid;					// 前子序的开始和结束游标
	int start2 = mid + 1, end2 = end;				// 后子序的开始和结束游标
	merge_sort_recursive(arr, reg, start1, end1);	// 递归分组
	merge_sort_recursive(arr, reg, start2, end2);
	// 以下开始merge动作
	int k = start;
	// 将小的放到目标队列指定位置
	while (start1 <= end1 && start2 <= end2) //前后子序的没有到游标最大位置
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];  // 比较前后子序各自游标指定的元素，小的放到目标队列中
	// 将前子序剩下的元素全部拷贝到目标队列
	while (start1 <= end1)
		reg[k++] = arr[start1++];
	// 将后子序剩下的元素全部拷贝到目标队列
	while (start2 <= end2)
		reg[k++] = arr[start2++];
	// reg数组最为中间队列，使用完会删除，因此需要把排序好的队列复制回原来的数组中。
	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}
//整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
template<typename T>
void merge_sort(T arr[], const int len) {
	T *reg = new T[len];
	merge_sort_recursive(arr, reg, 0, len - 1);
	delete[] reg;
}

int main(int argc, char* argv[]) {
	int arr[] = {9,4,2,5,3,1};
	int len = sizeof(arr) / sizeof(arr[0]);
	merge_sort<int>(arr, len);
	for (int i = 0; i < len; i++)
		printf(" %d", arr[i]);
	printf("\n");
	getchar();
	return 0;
}