#pragma once
#include "Shape.h"
class Point :
	public Shape
{
public:
	Point(int x, int y);
	~Point();
	virtual void draw() const override;
	void strongDraw() const;
	bool nearBy(int x, int y);
	int getX() const { return x; }
	int getY() const { return y; }
	void set(int x, int y) { this->x = x; this->y = y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
private:
	int x, y;
};

