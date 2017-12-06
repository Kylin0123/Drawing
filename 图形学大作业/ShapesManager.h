#pragma once
#include <vector>
#include "Point.h"
#include "Matrix.h"

class System;

class ShapesManager
{
public:
	ShapesManager();
	virtual ~ShapesManager();
	virtual void clearPointStack();
	virtual void drawAll(int mouseX, int mouseY) const = 0;
	virtual void down(int x, int y, Point* & focus_point) = 0;
	virtual void up(int x, int y) = 0;
	virtual void translate(int x, int y) = 0;
	virtual void rotate(float angle) = 0;
	virtual void scale(float s1, float s2) = 0;
	virtual void fillOrNot();
	virtual void cut(int x1, int y1, int x2, int y2);
	static void setWindowSize(int windowWidth, int windowHeight);
	static void setSystem(System* system);
protected:
	std::vector<Point> point_stack;
	static int windowWidth;
	static int windowHeight;
	static System* mySystem;
};

