#include <iostream>

using namespace std;

int factorial(const int N) {
	if (N <= 2)
		return N;
	else {
		return N * factorial(N-1);
	}
}

int main() {
	int n;
	while (1) {
		cin >> n;
		if (0 == n)	break;
		cout << factorial(n) << endl;
	}
}