#pragma once

#include "Rect.h"

class CutWin
{
public:
	CutWin(int x1, int y1, int x2, int y2);
	~CutWin();
	void draw() const;
	bool getIsCut() const { return isCut; }
	void setIsCut(bool isCut) { this->isCut = isCut; }
	int getTop() const { return cutRect.getTop(); }
	int getBottom() const { return cutRect.getBottom(); }
	int getLeft() const { return cutRect.getLeft(); }
	int getRight() const { return cutRect.getRight(); }
	bool nearBy(int x, int y);
	void moveFocusPointTo(int x, int y);
	void cutOrNot() { isCut = !isCut; }
private:
	Rect cutRect;
	Point* focus_point;
	bool isCut;
};

