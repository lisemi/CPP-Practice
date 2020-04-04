/*
三个空瓶可以换1瓶饮料，有一个特殊情况，当手头有2个空瓶可以向老板借一瓶喝，喝完把三个空瓶还给他。
请问空瓶数为n时可以换多少瓶饮料喝。
输入文件最多包含10组测试数据，每个数据占一行，仅包含一个正整数n（1<=n<=100），
表示小张手上的空汽水瓶数。n=0表示输入结束，你的程序不应当处理这一行。
设空瓶数为n，能换x瓶：
	n<2: 一瓶也换不了 x=0；
	n==2: 能换一瓶 x=1；
	n>2: 空瓶数=n-3，又由于三个空瓶可以换一瓶，那么实际上可以换的次数是=n-2，那么可以使用递归算法完成
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int drinkTime = 0;
void countDrink(const int emBottle) {	
	if (emBottle < 2)
		return;
	else {
		if (emBottle == 2)
			drinkTime++;
		if(emBottle >= 3){
			drinkTime++;
			countDrink(emBottle - 2);
		}
	}
}

int main(int argc, char *argv[]) {

	std::vector<int> emBottle;
	int loop = 10;
	while(loop>0) {
		string s;
		getline(cin, s);
		int num = atoi(s.c_str());
		if (num == 0)	break;
		if (num >= 1 && num <= 100) {
			emBottle.push_back(num);
			loop--;
		}
	}

	for (int i = 0; i< emBottle.size(); i++) {
		countDrink(emBottle.at(i));
		cout << drinkTime << endl;
		drinkTime = 0;
	}
	cin.get();
	return 0;
}