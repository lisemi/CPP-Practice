#include <iostream>
#include "myarray.h"

using namespace std;

int main(){
	Array  a1(10);
	{
		cout << "\na1: ";
		for (int i = 0; i<a1.length(); i++) {
			a1.setData(i, i);
			a1[i] = i;        // 调用[]操作符重载函数
		}
		for (int i = 0; i<a1.length(); i++) {
			cout << a1[i] << " ";
		}
		cout << endl;
	}

	Array a2 = a1;
	{
		cout << "\na2: ";
		for (int i = 0; i<a2.length(); i++) {
			cout << a2.getData(i) << " ";
		}
		cout << endl;
	}

	Array a3(5);
	{
		a3 = a1;
		a3 = a2 = a1;
		cout << "\na3: ";
		for (int i = 0; i<a3.length(); i++){
			cout << a3[i] << " ";
		}
		cout << endl;
	}
	// ==和!=
	{
		if (a3 == a1) {
			printf("equality\n");
		}
		else {
			printf("inequality\n");
		}

		if (a3 != a1) {
			printf("inequality\n");
		}
		else {
			printf("equality\n");
		}
	}

	system("pause");
	return 0;
}