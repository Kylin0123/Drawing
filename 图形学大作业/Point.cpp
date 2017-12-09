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
