/*
* non-virtual interface(NVI)手法:令用户通过public non-virtual成员函数间接调用
* private virtual函数，将这个non-virtual函数称为virtual函数的wrapper.wrapper确
* 保得以在一个virtual函数被调用之前设定好适当场景，并在调用结束之后清理场景.注
* 意此时用指针或引用调用该non-virtual成员函数时，该non-virtual成员函数调用的
* virtual函数取决于指针或引用的动态类型，即存在多态
*/
#include <iostream>
using namespace std;

enum ShapeColor { Red, Green, Blue };

class Shape{
public:
	void draw(ShapeColor color = Red) const{
		doDraw(color);
	}
private:
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle :public Shape{
public:

private:
	virtual void doDraw(ShapeColor color) const;
};

void Rectangle::doDraw(ShapeColor color) const{
	cout << "Rectangle's doDraw" << "color= " << color << endl;
}

void main4(){
	Shape*p = new Rectangle;
	p->draw();
}

