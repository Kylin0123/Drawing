#pragma once
#include <vector>
#include "Point.h"
#include "Matrix.h"

class ShapesManager
{
public:
	ShapesManager();
	virtual ~ShapesManager();
	virtual void clearPointStack();
	virtual void drawAll(int mouseX, int mouseY, bool isEditable) const = 0;
	virtual void down(int x, int y, bool & isEditable, Point* & focus_point) = 0;
	virtual void up(int x, int y, bool & isEditable) = 0;
	virtual void translate(int x, int y, bool isEditable) = 0;
	virtual void rotate(float angle, bool isEditable) = 0;
	virtual void scale(float s1, float s2, bool isEditable) = 0;
	static void setWindowSize(int windowWidth, int windowHeight);
protected:
	std::vector<Point> point_stack;
	static int windowWidth;
	static int windowHeight;
};

