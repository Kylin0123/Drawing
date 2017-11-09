#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Bezier.h"
#include "MyPolygon.h"
#include "Circle.h"
#include "Ellipise.h"
#include "LinesManager.h"
#include "BeziersManager.h"
#include "PolygonsManager.h"
#include "CirclesManager.h"
#include "EllipisesManager.h"
#include "ShapesManager.h"

class System
{
public:
	System();
	~System();
	void draw();
	void down(int x, int y);
	void up(int x, int y);
	enum InputType { LINE, BEZIER, POLYGON, CIRCLE, ELLIPISE, POLYGON_FILL
	};
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
private:
	LinesManager linesManager;
	BeziersManager beziersManager;
	PolygonsManager polygonsManager;
	CirclesManager circlesManager;
	EllipisesManager ellipisesManager;
	
	InputType inputType;
	PDrawPointFunc pDrawPointFunc;
	
	Point* focus_point;
	ShapesManager* shapesManager;

	int windowWidth, windowHeight;
	int mouseX, mouseY;
	bool isEditable;
};

