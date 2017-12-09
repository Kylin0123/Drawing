#include "CutRect.h"



CutRect::CutRect(int x1, int y1, int x2, int y2):
	//left(min(x1,x2)),
	//top(max(y1,y2)),
	//right(max(x1, x2)),
	//bottom(min(y1,y2)),
	//lt(left, top),
	//rt(right, top),
	//rb(right, bottom),
	//lb(left, bottom),
	rt(max(x1, x2), max(y1, y2)),
	lb(min(x1, x2), min(y1, y2))
{
}

CutRect::~CutRect()
{
}

void CutRect::draw() const
{
	int left = lb.getX();
	int bottom = lb.getY();
	int right = rt.getX();
	int top = rt.getY();
	lb.strongDraw();
	rt.strongDraw();
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

Point * CutRect::nearBy(int x, int y)
{
	if (lb.nearBy(x, y)) 
		return &lb;
	else if (rt.nearBy(x, y))
		return &rt;
	else
		return nullptr;
}
