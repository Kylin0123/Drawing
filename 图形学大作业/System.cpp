#include "System.h"

System::System():
	inputType(LINE),
	isEditable(false), 
	shapesManager(&linesManager),
	cutRect(100,100,200,200)
{
	ShapesManager::setSystem(this);
}


System::~System()
{
}	

void System::draw()
{
	linesManager.drawAll(mouseX, mouseY);
	beziersManager.drawAll(mouseX, mouseY);
	polygonsManager.drawAll(mouseX, mouseY);
	circlesManager.drawAll(mouseX, mouseY);
	ellipisesManager.drawAll(mouseX, mouseY);
	if (isCut) {
		cutRect.draw();
	}
}

void System::down(int x, int y)
{
	if (isCut) {
		focus_point = cutRect.nearBy(x, y);
	}
	else{
		shapesManager->down(x, y, focus_point);
	}
}

void System::up(int x, int y)
{
	/*if (polygonsManager.getIsFill()) {
		polygonsManager.refill();
	}*/
	shapesManager->up(x, y);
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
		shapesManager = &polygonsManager;
		break;
	case CIRCLE: 
		shapesManager = &circlesManager;
		break;
	case ELLIPISE: 
		shapesManager = &ellipisesManager;
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

void System::translate(int x, int y)
{
	shapesManager->translate(x, y);
}

void System::rotate(float angle)
{
	translate(-mouseX, -mouseY);
	shapesManager->rotate(angle);
	translate(mouseX, mouseY);
}

void System::scale(float s1, float s2)
{
	translate(-mouseX, -mouseY);
	shapesManager->scale(s1, s2);
	translate(mouseX, mouseY);
}

void System::fillOrNot()
{
	shapesManager->fillOrNot();
}

void System::cutOrNot()
{
	isCut = !isCut;
}

void System::cut()
{
	if (isCut) {
		doCut(cutRect.getLeft(),
			cutRect.getBottom(),
			cutRect.getRight(),
			cutRect.getTop());
	}
}

void System::doCut(int xmin, int ymin, int xmax, int ymax)
{
	if (!shapesManager) 
		return;
	shapesManager->cut(xmin, ymin, xmax, ymax);
}

std::string System::getStateString() const { 
	return isEditable ? "editable" : "drawing"; 
}

std::string System::getInputTypeString() const {
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
	default: 
		assert(0);
		return nullptr;
	}
}

void System::setDrawPointFunc(PDrawPointFunc pDrawPointFunc) {
	this->pDrawPointFunc = pDrawPointFunc;
	Shape::pDrawPointFunc = pDrawPointFunc;
}

void System::setIsCut(bool isCut)
{
	this->isCut = isCut;
}

void System::moveFocusPointTo(int x, int y)
{
	if (!focus_point)
		return;
	focus_point->set(x, y);
	if (polygonsManager.getIsFill())
		polygonsManager.refill();
}

void System::clearPointStack()
{
	shapesManager->clearPointStack();
}