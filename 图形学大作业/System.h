#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "ShapesManager.h"
#include "LinesManager.h"
#include "BeziersManager.h"
#include "PolygonsManager.h"
#include "CirclesManager.h"
#include "EllipisesManager.h"
#include "CutRect.h"

class System
{
public:
	System();
	~System();
	void draw();
	void down(int x, int y);
	void up(int x, int y);
	void fillOrNot();
	void cutOrNot();
	void cut();
	void doCut(int xmin, int ymin, int xmax, int ymax);

	/*transform*/
	void translate(int x, int y);
	void rotate(float angle);
	void scale(float s1, float s2);

	/*built-in types*/
	enum InputType { LINE, BEZIER, POLYGON, CIRCLE, ELLIPISE };
	typedef void(WINAPI *PDrawPointFunc)(GLint, GLint);
	
	/*setter*/
	void setInputType(InputType inputType);
	void setWindowSize(int width, int height);
	void setMousePos(int x, int y);
	void setIsEditable(bool isEditable);
	void setDrawPointFunc(PDrawPointFunc pDrawPointFunc);
	void setIsCut(bool isCut);

	/*getter*/
	InputType getInputType() const;
	int getMouseX() const { return mouseX; }
	int getMouseY() const { return mouseY; }
	int getWindowSizeX() const { return windowWidth; }
	int getWindowSizeY() const { return windowHeight; }
	bool getIsEditable() const { return isEditable; }
	bool getIsCut() const { return isCut; }
	std::string getStateString() const;
	std::string getInputTypeString() const;
	
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
	bool isCut;
public:
	CutRect cutRect;
};
