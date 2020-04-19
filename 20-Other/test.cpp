#include <iostream>
#include <map>

using namespace std;

int main(){
	map<int, int> a = { { 1, 12 },{ 2, 23 },{ 3, 34 },{ 4, 45 },{ 5, 56 },{ 6, 67 } };

	auto iter = a.begin();
	while (iter != a.end()) {
		if (iter->second > 30) {
			a.erase(iter++);
		}
		else {
			++iter;
		}
	}
	for (const auto &element : a) {
		cout << element.first << " : " << element.second << endl;
	}
	cin.get();
	return 0;
}