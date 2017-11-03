#pragma once
#include "Shape.h"
#include "Point.h"
class Circle :
	public Shape
{
public:
	Circle(const Point & centre, int radius);
	~Circle();
	virtual void draw() const override;
private:
	Point centre;
	int radius;
	void draw8points (const Point & centre, int cur_x, int cur_y) const;
};

