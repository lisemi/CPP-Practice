// 二分查找（折半查找）：对于已排序，若无序，需要先排序

// 非递归
#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*
 * v：被查找数列
 * value：被查找的值
 * low：数列的最小下标
 * high：数列的最大下标
*/
int BinarySearch(const vector<int> v, int value, int low, int high) {
	if (v.size() <= 0) {
		return -1;
	}
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (v[mid] == value) {
			return mid;
		}
		else if (v[mid] > value) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return -1;
}

// 递归
int BinarySearch2(vector<int> v, int value, int low, int high)
{
	if (low > high)
		return -1;
	int mid = low + (high - low) / 2;
	if (v[mid] == value)
		return mid;
	else if (v[mid] > value)
		return BinarySearch2(v, value, low, mid - 1);
	else
		return BinarySearch2(v, value, mid + 1, high);
}

int main1(int argc, char* argv[]) {
	int arr[] = { 2,3,7,5,4,19,8,10,1,6 };
	vector<int> vc;
	vc.clear();

	cout << "find 6 in array" << endl;
	set<int> s(arr, arr + sizeof(arr)/sizeof(arr[0]));
	vc.assign(s.begin(), s.end());

	cout << BinarySearch(vc, 19, 0, 9) << endl;

	cin.get();
	return 0;
}