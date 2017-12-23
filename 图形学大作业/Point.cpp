#include "Point.h"


Point::Point(int x, int y):
	x(x),y(y)
{
}

Point::~Point()
{
}

void Point::draw() const
{
	pDrawPointFunc(x, y);
}

void Point::strongDraw() const
{
	for (int i = -5; i <= 5; i++) {
		pDrawPointFunc(x + i, y - 5);
		pDrawPointFunc(x + i, y + 5);
		pDrawPointFunc(x - 5, y + i);
		pDrawPointFunc(x + 5, y + i);
	}
}

bool Point::nearBy(int x, int y)
{
	if (abs(this->x - x) + abs(this->y - y) <= 10)
		return true;
	else
		return false;
}

void Point::set(int x, int y) 
{ 
	setX(x);
	setY(y);
}

void Point::setX(int x) { this->x = x; }

void Point::setY(int y) { this->y = y; }

void Point::moveFocusPointTo(int x, int y)
{
	set(x, y);
}

void Point::translate(int x, int y)
{
	this->x += x;
	this->y += y;
}

void Point::rotate(float angle)
{
	float m[3][3] = {
		{ cos(angle), -sin(angle), 0 },
		{ sin(angle), cos(angle), 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	change(matrix);
}

void Point::scale(float s1, float s2)
{
	float m[3][3] = {
		{ s1, 0, 0 },
		{ 0, s2, 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	change(matrix);
}
