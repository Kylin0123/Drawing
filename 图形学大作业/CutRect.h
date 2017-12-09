#pragma once
#include "Point.h"
class CutRect
{
public:
	CutRect(int x1, int y1, int x2, int y2);
	~CutRect();
	void draw() const;
	Point* nearBy(int x, int y);
	int getTop() const { return rt.getY();/*return top;*/ };
	int getLeft() const { return lb.getX();/*return left;*/ }
	int getRight() const { return rt.getX();/*return right;*/ }
	int getBottom() const { return lb.getY();/*return bottom;*/ }
	void setTop(int top) {
		//this->top = top;
		//lt.setY(top);
		rt.setY(top);
	}
	void setLeft(int left) {
		//this->left = left; 
		//lt.setX(left);
		lb.setX(left);
	}
	void setRight(int right) { 
		//this->right = right; 
		rt.setX(right);
		//rb.setX(right);
	}
	void setBottom(int bottom) { 
		//this->bottom = bottom; 
		lb.setY(bottom);
		//rb.setY(bottom);
	}
private:
	//int top, left, right, bottom;
	Point lb, rt;
};

