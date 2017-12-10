#pragma once
#include "Point.h"

class Rect
{
public:
	Rect(int x1, int y1, int x2, int y2);
	~Rect();
	void reshape(const std::vector<Point> & points);
	void draw() const;
	void strongDraw() const;
	void translate(int dx, int dy);
	Point* nearBy(int x, int y);
	Point* get_lt() { return &lt; }
	Point* get_lb() { return &lb; }
	Point* get_rt() { return &rt; }
	Point* get_rb() { return &rb; }
	int getTop() const { return rt.getY(); };
	int getLeft() const { return lb.getX(); }
	int getRight() const { return rt.getX(); }
	int getBottom() const { return lb.getY(); }
	int getMidX() const { return (getLeft() + getRight()) / 2; }
	int getMidY() const { return (getTop() + getBottom()) / 2; }
	void setTop(int top) {
		rt.setY(top);
		lt.setY(top);
	}
	void setLeft(int left) {
		lb.setX(left);
		lt.setX(left);
	}
	void setRight(int right) { 
		rt.setX(right);
		rb.setX(right);
	}
	void setBottom(int bottom) { 
		lb.setY(bottom);
		rb.setY(bottom);
	}
private:
	Point lt, rt;   //左上、*右上
	Point lb, rb;   //*左下、右下
};

