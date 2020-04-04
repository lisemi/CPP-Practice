#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
template <typename T>
void print(vector<T> vc) {
	for (vector<T>::iterator it = vc.begin(); it != vc.end(); it++) {
		cout << *it << " " << endl;
	}
}

void test_merge() {
	vector<int> v1, v2, v3;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);

	v2.push_back(2);
	v2.push_back(4);
	v2.push_back(6);

	v3.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	print<int>(v3);
}

class Student {
public:
	Student(string name, int id) : m_name(name),m_id(id){}
	void printT() {
		cout << "id : " << m_id << " name : " << m_name << endl;
	}
public:
	string m_name;
	int m_id;
};

bool compareS(Student &S1, Student &S2) {
	return (S1.m_id < S2.m_id);
}

void test_sort() {
	Student s1("老大", 1);
	Student s2("老二", 2);
	Student s3("老三", 3);
	Student s4("老四", 4);
	vector<Student> v1;
	v1.push_back(s4);
	v1.push_back(s1);
	v1.push_back(s3);
	v1.push_back(s2);

	for (vector<Student>::iterator it = v1.begin(); it != v1.end(); it++) {
		it->printT();
	}
	sort(v1.begin(), v1.end(), compareS);
	for (vector<Student>::iterator it = v1.begin(); it != v1.end(); it++) {
		it->printT();
	}
}

// 随机打乱顺序
void test_random_shuffle() {
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	random_shuffle(v1.begin(), v1.end());
	print<int>(v1);

	string str = "abcdfghijk";
	random_shuffle(str.begin(), str.end());
	cout << "str : " << str << endl;
}

// 倒序
void test_reverse() {
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(7);
	reverse(v1.begin(), v1.end());
	print<int>(v1);
}

int main(int argc, char* argv[]){
	test_sort();
	//test_merge();
	//test_random_shuffle();
	//test_reverse();
	cin.get();
	return 0;
}