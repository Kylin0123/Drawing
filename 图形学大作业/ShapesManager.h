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
	void clearPointStack();
	virtual void clearCurrent() = 0;
	virtual void drawAll(int mouseX, int mouseY) const = 0;
	virtual void down(int x, int y) = 0;
	virtual void up(int x, int y) = 0;
	virtual void moveFocusPointTo(int x, int y) = 0;
	virtual void translate(int x, int y) = 0;
	virtual void rotate(float angle) = 0;
	virtual void scale(float s1, float s2) = 0;
	virtual void fillOrNot() = 0;
	virtual void cut(int xmin, int ymin, int xmax, int ymax) = 0;
	static void setSystem(System* system);
protected:
	std::vector<Point> point_stack;
	static System* mySystem;
};

