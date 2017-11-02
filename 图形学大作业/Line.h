#pragma once
#include "Shape.h"
#include "Point.h"
class Line :
	public Shape
{
public:
	Line(const Point & start, const Point & end);
	~Line();
	void setEnd(const Point & end);
	virtual void draw() const override;
private:
	Point start, end;
};

