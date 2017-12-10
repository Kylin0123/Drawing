#include "Rect.h"



Rect::Rect(int x1, int y1, int x2, int y2):
	rt(max(x1, x2), max(y1, y2)),
	lb(min(x1, x2), min(y1, y2)),
	lt(min(x1, x2), max(y1, y2)),
	rb(max(x1, x2), min(y1, y2))
{
}

Rect::~Rect()
{
}

void Rect::reshape(const std::vector<Point>& points)
{
	int max_x = INT_MIN;
	int max_y = INT_MIN;
	int min_x = INT_MAX;
	int min_y = INT_MAX;
	for (const Point & p : points) {
		max_x = max(max_x, p.getX());
		max_y = max(max_y, p.getY());
		min_x = min(min_x, p.getX());
		min_y = min(min_y, p.getY());
	}
	setTop(max_y);
	setBottom(min_y);
	setLeft(min_x);
	setRight(max_x);
}

void Rect::draw() const
{
	int left = lb.getX();
	int bottom = lb.getY();
	int right = rt.getX();
	int top = rt.getY();
	
	glEnd();
	glLineStipple(2, 0x5555);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2i(left, top);
	glVertex2i(right, top);
	glVertex2i(right, top);
	glVertex2i(right, bottom);
	glVertex2i(right, bottom);
	glVertex2i(left, bottom);
	glVertex2i(left, bottom);
	glVertex2i(left, top);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_POINTS);
}


void Rect::strongDraw() const
{
	lb.strongDraw();
	rt.strongDraw();
	lt.strongDraw();
	rb.strongDraw();
	draw();
}


void Rect::translate(int dx, int dy)
{
	lb.translate(dx, dy);
	rb.translate(dx, dy);
	lt.translate(dx, dy);
	rt.translate(dx, dy);
}

Point * Rect::nearBy(int x, int y)
{
	if (lb.nearBy(x, y))
		return &lb;
	else if (rt.nearBy(x, y))
		return &rt;
	else if (lt.nearBy(x, y))
		return &lt;
	else if (rb.nearBy(x, y))
		return &rb;
	else
		return nullptr;
}
