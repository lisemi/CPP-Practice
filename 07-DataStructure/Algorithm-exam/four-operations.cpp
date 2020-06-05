/*
* 输入一个字符串表示的由加减乘除以及整数构成的式子，求出答案；
*/
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int calculate(int len, char *expStr){
	int m = len;
	int num[10] = { 0 };
	int sig[10] = { 0 };
	int result[10] = { 0 };
	int j = 0, k = 0, a = 0;
	for (int i = 0; i < len; ++i){
		if (isdigit(expStr[i]))
			num[j++] = expStr[i] - '0'; //求字符数字的十进制数字值，如’6‘=54,而’0‘=48,所以’6‘-’0‘=6；
		else
			sig[k++] = expStr[i];
	}
	for (a = 0; a <= k - 1; ++a) { 
		if ('*' == sig[a]){
			num[a] = num[a] * num[a + 1];
			for (int i = a; i < k - 1; ++i){
				sig[i] = sig[i + 1];
			}
			sig[k - 1] = 0;
			for (int i = a + 1; i <= k - 1; ++i){
				num[i] = num[i + 1];
			}
			num[k] = 0;
			a = -1; //如果有运算，则从最先的开始，因为进入下一个循环要加一，所以这里设置为-1
		}
		if ('/' == sig[a]){
			num[a] = num[a] / num[a + 1];
			for (int i = a; i < k - 1; ++i){
				sig[i] = sig[i + 1];
			}
			sig[k - 1] = 0;
			for (int i = a + 1; i <= k - 1; ++i){
				num[i] = num[i + 1];
			}
			num[k] = 0;
			a = -1;
		}
	}

	for (a = 0; a <= k - 1; ++a){
		if ('+' == sig[a]){
			num[a] = num[a] + num[a + 1];
			for (int i = a; i < k - 1; ++i){
				sig[i] = sig[i + 1];
			}
			sig[k - 1] = 0;
			for (int i = a + 1; i <= k - 1; ++i){
				num[i] = num[i + 1];
			}
			num[k] = 0;
			a = -1;
		}
		if ('-' == sig[a]){
			num[a] = num[a] - num[a + 1];
			for (int i = a; i < k - 1; ++i){
				sig[i] = sig[i + 1];
				//a = -1;
			}
			sig[k - 1] = 0;
			for (int i = a + 1; i <= k - 1; ++i){
				num[i] = num[i + 1];
			}
			num[k] = 0;
			a = -1;
		}
	}
	return num[0];
}

int main(){
	string s;
	getline(cin, s);
	cout << s << " = " << calculate(s.length(), const_cast<char*>(s.c_str()));
	cin.get();
	return 0;
}