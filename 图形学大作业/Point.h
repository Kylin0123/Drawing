#pragma once
#include "Shape.h"
#include "Matrix.h"

class Point :
	public Shape
{
public:
	Point(int x, int y);
	~Point();
	virtual void draw() const override;
	virtual void strongDraw() const override;

	template<typename T>
	void change(const Matrix<T> &m) {
		T v[3][1] = { (T)x, (T)y, (T)1 };
		Matrix<T> vec((T*)v, 3, 1);
		Matrix<T> ret = m * vec;
		x = std::round(ret.get(0, 0));
		y = std::round(ret.get(1, 0));
	}

	bool nearBy(int x, int y);
	int getX() const { return x; }
	int getY() const { return y; }
	void set(int x, int y) { this->x = x; this->y = y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
private:
	int x, y;
};

