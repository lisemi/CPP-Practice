#include <iostream>

//算法复杂度O(N). 找出数组arr中两个数相减的最大值
int maxValueOfSubtraction(int arr[], int len) {
	int max = 0;// when j == i
	int i = 0;
	int sub;
	for (int j = 1; j < len; j++) {
		sub = arr[j] - arr[i];
		if (sub > max)
			max = sub;
		else if (sub < 0)//means there is a number smaller than a[i](i initial value is 0)
			i = j;
	}
	return max;
}

int main() {
	int arr[] = {2,24,26,1,16,18,22,10,15,21};
	int len = sizeof(arr) / sizeof(arr[0]);
	std::cout << maxValueOfSubtraction(arr, len) << std::endl;
	std::cin.get();
	return 0;
}