/*
写出一个程序，接受一个十六进制的数，输出该数值的十进制表示。（多组同时输入 ）


输入描述:
输入一个十六进制的数值字符串。


输出描述:
输出该数值的十进制字符串。


输入例子1:
0xA

输出例子1:
10
*/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	int dec=0;
	// hex to decimal
	while ((cin >> hex >> dec)) {
		cout << dec << endl;
	}

	// octonary to decimal
	while ((cin >> hex >> dec)) {
		cout << dec << endl;
	}
	return 0;
}