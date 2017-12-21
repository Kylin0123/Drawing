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
		x = max(cutRect.get_lb()->getX(), x);
		y = max(cutRect.get_lb()->getY(), y);
		focus_point->set(x, y);
		cutRect.get_lt()->setY(y);
		cutRect.get_rb()->setX(x);
	}
	else if (focus_point == cutRect.get_rb()) {
		x = max(cutRect.get_lt()->getX(), x);
		y = min(cutRect.get_lt()->getY(), y);
		focus_point->set(x, y);
		cutRect.get_lb()->setY(y);
		cutRect.get_rt()->setX(x);
	}
	else if (focus_point == cutRect.get_lt()) {
		x = min(cutRect.get_rb()->getX(), x);
		y = max(cutRect.get_rb()->getY(), y);
		focus_point->set(x, y);
		cutRect.get_rt()->setY(y);
		cutRect.get_lb()->setX(x);
	}
	else if (focus_point == cutRect.get_lb()) {
		x = min(cutRect.get_rt()->getX(), x);
		y = min(cutRect.get_rt()->getY(), y);
		focus_point->set(x, y);
		cutRect.get_rb()->setY(y);
		cutRect.get_lt()->setX(x);
	}
	else {
		assert(0);
	}
}
