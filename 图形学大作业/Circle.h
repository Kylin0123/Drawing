#pragma once
#include "Shape.h"
#include "Point.h"
#include "Rect.h"

class Circle :
	public Shape
{
public:
	Circle(const Point & centre, int radius);
	~Circle();
	virtual void draw() const override;
	virtual void strongDraw() const override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual bool nearBy(int x, int y) override;
private:
	Point centre;
	int radius;
	void draw8points(int cur_x, int cur_y) const;
	Rect editRect;
	Point* focus_point;
};

