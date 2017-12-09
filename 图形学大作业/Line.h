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
	bool getCrossPoint(const Line & line, Point & ret);
	Point getStart() const { return start; }
	Point getEnd() const { return end; }
private:
	Point start, end;
};

