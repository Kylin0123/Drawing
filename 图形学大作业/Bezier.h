#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>
#include "Rect.h"

class Bezier :
	public Shape
{
public:
	Bezier(const std::vector<Point> & points);
	~Bezier();
	virtual void draw() const override;
	virtual void strongDraw() const override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	bool nearBy(int x, int y);
private:
	std::vector<Point> points;
	Rect editRect;
	Point* focus_point;
};

