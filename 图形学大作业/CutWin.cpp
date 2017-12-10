#include "CutWin.h"



CutWin::CutWin(int x1, int y1, int x2, int y2):
	cutRect(x1, y1, x2, y2), isCut(false)
{
}


CutWin::~CutWin()
{
}

void CutWin::draw() const {
	if (isCut) cutRect.strongDraw();
}

bool CutWin::nearBy(int x, int y)
{
	if (focus_point = cutRect.nearBy(x, y)) {
		return true;
	}
	return false;
}

void CutWin::moveFocusPointTo(int x, int y)
{
	int x0 = focus_point->getX();
	int y0 = focus_point->getY();
	if (focus_point == cutRect.get_rt()) {
		focus_point->set(x, y);
		cutRect.get_lt()->setY(y);
		cutRect.get_rb()->setX(x);
	}
	else if (focus_point == cutRect.get_rb()) {
		focus_point->set(x, y);
		cutRect.get_lb()->setY(y);
		cutRect.get_rt()->setX(x);
	}
	else if (focus_point == cutRect.get_lt()) {
		focus_point->set(x, y);
		cutRect.get_rt()->setY(y);
		cutRect.get_lb()->setX(x);
	}
	else if (focus_point == cutRect.get_lb()) {
		focus_point->set(x, y);
		cutRect.get_rb()->setY(y);
		cutRect.get_lt()->setX(x);
	}
	else {
		assert(0);
	}
}
