#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>

class MyPolygon :
	public Shape
{
public:
	MyPolygon(const std::vector<Point> & points);
	~MyPolygon();
	virtual void draw() const override;
private:
	std::vector<Point> points;
};

