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
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;

	template<typename T>
	void change(const Matrix<T> &m) {
		T v[3][1] = { (T)x, (T)y, (T)1 };
		Matrix<T> vec((T*)v, 3, 1);
		Matrix<T> ret = m * vec;
		x = std::round(ret.get(0, 0));
		y = std::round(ret.get(1, 0));
	}

	void set(int x, int y);
	void setX(int x);
	void setY(int y);

	bool nearBy(int x, int y) const;
	int getX() const { return x; }
	int getY() const { return y; }
	
private:
	int x, y;
};

