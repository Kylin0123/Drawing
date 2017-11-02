#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>

class Bezier :
	public Shape
{
public:
	Bezier(const std::vector<Point> & points);
	~Bezier();
	virtual void draw() const override;
private:
	std::vector<Point> points;
};

