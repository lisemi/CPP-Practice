/*
插值查找:
插值查找的折半查找类似，只是他们计算mid值的公式不同而已
mid值计算：(key:要查找的值，low：数组左索引，high：数组右索引)
                  key + a[low]
	mid = low + ----------------(high - low)
	            a[high] - a[low]
*/
#include <stdio.h>

int InsertionSearch(int a[], int value, int low, int high)
{
	int mid = low + (value - a[low]) / (a[high] - a[low])*(high - low);
	if (a[mid] == value)
		return mid;
	if (a[mid]>value)
		return InsertionSearch(a, value, low, mid - 1);
	if (a[mid]<value)
		return InsertionSearch(a, value, mid + 1, high);
}

int main2(int argc, char* argv[]) {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };

	printf("test InsertionSearch:\n");
	printf("find 4 in the array, index=%d\n", InsertionSearch(arr, 4, 0, 9));

	getchar();
	return 0;
}