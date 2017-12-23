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
	virtual void drawAll(int mouseX, int mouseY) const = 0;
	virtual void down(int x, int y) = 0;
	virtual void up(int x, int y) = 0;
	virtual void fillOrNot() = 0;
	virtual void cut(int xmin, int ymin, int xmax, int ymax) = 0;

	void moveFocusPointTo(int x, int y);
	void translate(int x, int y);
	void rotate(float angle);
	void scale(float s1, float s2);
	void clearPointStack();
	void clearCurrent();
	static void setSystem(System* system);
	bool nearBy(int x, int y);
protected:
	std::vector<Point> point_stack;
	static System* mySystem;
	std::vector<std::shared_ptr<Shape>> shapes;
};

