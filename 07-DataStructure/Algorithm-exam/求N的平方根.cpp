/*
* 方法一：二分法
* 就是定义一个最小值0和最大值number，把一个数取一个中间值（0+number）/2，然后平方，
* 如果平方大于该数值，就把中间值赋给最大值，否者就把中间值赋给最小值，一直循环，直到取到想要的精度为止
*/
#include <iostream>
#include <string>
using namespace std;

double sqrt1(double x) {
	double EPSINON = 0.00001;
	double low = 0.0;
	double high = x;
	double mid = (low + high) / 2;
	while ((high - low) > EPSINON) {
		if (mid*mid > x) {
			high = mid;
		}
		else {
			low = mid;
		}
		mid = (high + low) / 2;
	}
	return mid;
}

/*
* 牛顿迭代法，公式:xi=(x+n/x)/2
*/
double sqrt2(double x) {
	if (x == 0) return 0;
	double last = 0.0;
	double res = 1.0;
	while (res != last)
	{
		last = res;
		res = (res + x / res) / 2;
	}
	return res;
}


int main(int argc, char* argv[]) {
	double N;
	while (cin >> N) {
		cout << sqrt2(N) << endl;
		N = 0;
	}
	return 0;
}
