#pragma once
#include "Shape.h"
#include "Point.h"
#include "Cutable.h"

class Line :
	public Shape, public Cutable
{
public:
	Line(const Point & start, const Point & end);
	~Line();
	void setEnd(const Point & end);
	virtual void draw() const override;
	virtual void strongDraw() const override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual bool cut(int xmin, int ymin, int xmax, int ymax) override;
	virtual bool nearBy(int x, int y) override;

	Point getStart() const { return start; }
	Point getEnd() const { return end; }
private:
	Point start, end;
	Point* focus_point;
};

