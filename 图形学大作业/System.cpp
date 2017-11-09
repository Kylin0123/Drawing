#include "System.h"

System::System():
	inputType(LINE), isEditable(false), shapesManager(&linesManager)
{
}


System::~System()
{
}	

void System::draw()
{
	linesManager.drawAll(mouseX, mouseY, isEditable);
	beziersManager.drawAll(mouseX, mouseY, isEditable);
	polygonsManager.drawAll(mouseX, mouseY, isEditable);
	circlesManager.drawAll(mouseX, mouseY, isEditable);
	ellipisesManager.drawAll(mouseX, mouseY, isEditable);
}

void System::down(int x, int y)
{
	shapesManager->down(x, y, isEditable, focus_point);
}

void System::up(int x, int y)
{
	shapesManager->up(x, y, isEditable);
}

void System::setInputType(InputType inputType)
{
	this->inputType = inputType;

	shapesManager->clearPointStack();
	isEditable = false;

	switch (inputType) {
	case LINE: 
		shapesManager = &linesManager;
		break;
	case BEZIER: 
		shapesManager = &beziersManager;
		break;
	case POLYGON: 
		polygonsManager.setFill(false);
		shapesManager = &polygonsManager;
		break;
	case CIRCLE: 
		shapesManager = &circlesManager;
		break;
	case ELLIPISE: 
		shapesManager = &ellipisesManager;
		break;
	case POLYGON_FILL:
		polygonsManager.setFill(true);
		shapesManager = &polygonsManager;
		break;
	default:
		break;
	}
}

System::InputType System::getInputType() const
{
	return inputType;
}

void System::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	shapesManager->setWindowSize(width, height);
}

void System::setMousePos(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void System::setIsEditable(bool isEditable)
{
	this->isEditable = isEditable;
}

std::string System::getInputTypeString() {
	switch (inputType) {
	case LINE: 
		return "LINE";
	case BEZIER: 
		return "BEZIER";
	case POLYGON: 
		return "POLYGON";
	case CIRCLE: 
		return "CIRCLE";
	case ELLIPISE: 
		return "ELLIPISE";
	case POLYGON_FILL:
		return "POLYGON_FILL";
	default: 
		assert(0);
	}
}

void System::setDrawPointFunc(PDrawPointFunc pDrawPointFunc) {
	this->pDrawPointFunc = pDrawPointFunc;
	Shape::pDrawPointFunc = pDrawPointFunc;
}

void System::moveFocusPointTo(int x, int y)
{
	if (!focus_point)
		return;
	focus_point->set(x, y);
}

void System::clearPointStack()
{
	shapesManager->clearPointStack();
}