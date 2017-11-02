#pragma once
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Bezier.h"
#include "MyPolygon.h"
#include <vector>
#include <memory>

class System
{
public:
	System();
	~System();
	void draw();
	void down(int x, int y);
	void up(int x, int y);
	void addPoint(int x, int y);
	void addLine(int x1, int y1, int x2, int y2);
	void addBezier();
	void addMyPolygon();
	enum InputType { LINE, BEZIER, POLYGON, FILL };
	void setInputType(InputType inputType);
	InputType getInputType() const;
	void setWindowSize(int width, int height);
	void setMousePos(int x, int y);
	void setIsEditable(bool isEditable);
	int getMouseX() const { return mouseX; }
	int getMouseY() const { return mouseY; }
	int getWindowSizeX() const { return windowWidth; }
	int getWindowSizeY() const { return windowHeight; }
	bool getIsEditable() const { return isEditable; }
	typedef void(WINAPI *PDrawPointFunc)(GLint, GLint);
	void setDrawPointFunc(PDrawPointFunc pDrawPointFunc);
	void setFocusPoint(int x, int y);
	void clearPointStack();
	const int bezierNum;
private:
	std::vector<std::shared_ptr<Point> > points;
	std::vector<std::shared_ptr<Line> > lines;
	std::vector<std::shared_ptr<Bezier> > beziers;
	std::vector<std::shared_ptr<MyPolygon> > polygons;
	InputType inputType;
	PDrawPointFunc pDrawPointFunc;
	std::vector<Point> point_stack;
	Point* focus_point;
	int windowWidth, windowHeight;
	int mouseX, mouseY;
	bool isEditable;
};

