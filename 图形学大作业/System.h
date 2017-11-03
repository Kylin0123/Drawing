#pragma once
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Bezier.h"
#include "MyPolygon.h"
#include "Circle.h"
#include <vector>
#include <memory>
#include <cassert>

class System
{
public:
	System();
	~System();
	void draw();
	void down(int x, int y);
	void up(int x, int y);
	void addPoint(int x, int y);
	void addLine(const Point & p1, const Point & p2);
	void addBezier();
	void addMyPolygon();
	void addCircle(const Point & p1, const Point & p2);
	enum InputType { LINE, BEZIER, POLYGON, CIRCLE, ELLIPSE, FILL };
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
	std::string getStateString() { return isEditable ? "editable" : "drawing"; }
	std::string getInputTypeString();
	typedef void(WINAPI *PDrawPointFunc)(GLint, GLint);
	void setDrawPointFunc(PDrawPointFunc pDrawPointFunc);
	void moveFocusPointTo(int x, int y);
	void clearPointStack();
	const int bezierNum;
protected:
	std::tuple<Point, int> caculateCirclePos(const Point & start, const Point & end);
private:
	std::vector<std::shared_ptr<Point> > points;
	std::vector<std::shared_ptr<Line> > lines;
	std::vector<std::shared_ptr<Bezier> > beziers;
	std::vector<std::shared_ptr<MyPolygon> > polygons;
	std::vector<std::shared_ptr<Circle> > circles;
	InputType inputType;
	PDrawPointFunc pDrawPointFunc;
	std::vector<Point> point_stack;
	Point* focus_point;
	int windowWidth, windowHeight;
	int mouseX, mouseY;
	bool isEditable;
};

