/*
解题思路：
	三角形三个点分别为A、B、C，如果某个点P在三角形能，
那么会有ABP、ACP和BCP的面积等于ABC的面积
已知三点求三角形面积方法有二：
（1）向量法：
	向量的叉乘在定义上有：两个向量进行叉乘得到的是一个向量，方向垂直于这两
	个向量构成的平面，大小等于这两个向量组成的平行四边形的面积。
	求向量AB（x2-x1,y2-y1），AC(x3-x1,y3-x3)然后求ABxAC(求AB AC的行列式，即AB.X*AC.Y - AC.Y*AC.X)然后将结果的绝对值除以2.
（2）海伦公式：
	 AB=a BC =b AC=c p=(a+b+c)/2 面积S=sqrt(p*(p-a)*(p-b)*(p-c)).
*/

#include <iostream>
#include <math.h>
using namespace std;
#define ABS_FLOAT_0 0.0001
struct point_float
{
	float x;
	float y;
};

float GetTriangleSquar(const point_float pt0, const point_float pt1, const point_float pt2)
{
	point_float AB, BC;
	AB.x = pt1.x - pt0.x;
	AB.y = pt1.y - pt0.y;
	BC.x = pt2.x - pt1.x;
	BC.y = pt2.y - pt1.y;
	return fabs((AB.x * BC.y - AB.y * BC.x)) / 2.0f;
}

bool IsInTriangle(const point_float A, const point_float B, const point_float C, const point_float D)
{
	float SABC, SADB, SBDC, SADC;
	SABC = GetTriangleSquar(A, B, C);
	SADB = GetTriangleSquar(A, D, B);
	SBDC = GetTriangleSquar(B, D, C);
	SADC = GetTriangleSquar(A, D, C);
	float SumSuqar = SADB + SBDC + SADC;
	if ((-ABS_FLOAT_0 < (SABC - SumSuqar)) && ((SABC - SumSuqar) < ABS_FLOAT_0)){
		return true;
	}
	else{
		return false;
	}
}

int main(int argc, char* argv[]) {
	point_float point_a = { 2.0, 2.0 };
	point_float point_b = { 7.0, 2.0 };
	point_float point_c = { 5.0, 6.0 };
	point_float point_p = { 7.0, 3.0 };
	
	cout << "point_p is in the triangle : " << IsInTriangle(point_a, point_b, point_c, point_p) << endl;
	cin.get();
	return 0;
}
