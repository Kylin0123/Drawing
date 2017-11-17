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

/*void Point::change(const Matrix<int> &m)
{
	int vec[3][1] = { x, y, 1 };
	Matrix<int> m1((int*)vec, 3, 1);
	Matrix<int> ret = m * m1;
	x = ret.get(0, 0);
	y = ret.get(1, 0);
}*/

void Point::strongDraw() const
{
	for (int i = 1; i <= 4; i++) {
		pDrawPointFunc(x - i, y - i);
		pDrawPointFunc(x - i, y + i);
		pDrawPointFunc(x + i, y - i);
		pDrawPointFunc(x + i, y + i);
	}
	pDrawPointFunc(x, y);
	
}

bool Point::nearBy(int x, int y)
{
	if (abs(this->x - x) + abs(this->y - y) <= 10)
		return true;
	else
		return false;
}
