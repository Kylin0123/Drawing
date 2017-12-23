#include "System.h"

System::System():
	inputType(LINE),
	isEditable(false),
	isDragable(true),
	shapesManager(&linesManager),
	cutWin(100,100,200,200),
	imageSaver(this)
{
	ShapesManager::setSystem(this);
}


System::~System()
{
}	

void System::draw()
{
	cutWin.draw();
	linesManager.drawAll(mouseX, mouseY);
	beziersManager.drawAll(mouseX, mouseY);
	polygonsManager.drawAll(mouseX, mouseY);
	circlesManager.drawAll(mouseX, mouseY);
	ellipisesManager.drawAll(mouseX, mouseY);
}

void System::draw3D()
{
	
}

void System::down(int x, int y)
{
	if (inputType == InputType::CHOOSE) {
		if (linesManager.nearBy(x, y)) {
			inputType = LINE;
			setIsEditable(true);
		}
		else if (beziersManager.nearBy(x, y)) {
			inputType = BEZIER;
			setIsEditable(true);
		}
		else if (circlesManager.nearBy(x, y)) {
			inputType = CIRCLE;
			setIsEditable(true);
		}
		else if (ellipisesManager.nearBy(x, y)) {
			inputType = ELLIPISE;
			setIsEditable(true);
		}
		else if (polygonsManager.nearBy(x, y)) {
			inputType = POLYGON;
			setIsEditable(true);
		}
		else {

		}
		return;
	}
	if (cutWin.getIsCut()) {
		if (cutWin.nearBy(x, y)) {

		}
		else {
			cutWin.setIsCut(false);
			isDragable = false;
		}
	}
	else{
		shapesManager->down(x, y);
	}
}

void System::up(int x, int y)
{
	shapesManager->up(x, y);
	isDragable = true;
}

void System::setInputType(InputType inputType)
{
	this->inputType = inputType;

	shapesManager->clearPointStack();
	setIsEditable(false);

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
	shapesManager->rotate(angle);
}

void System::scale(float s1, float s2)
{
	shapesManager->scale(s1, s2);
}

void System::fillOrNot()
{
	shapesManager->fillOrNot();
}

void System::cutOrNot()
{
	if(getIsEditable())
		cutWin.cutOrNot();
}

void System::cut()
{
	if (cutWin.getIsCut()) {
		doCut(cutWin.getLeft(),
			cutWin.getBottom(),
			cutWin.getRight(),
			cutWin.getTop());
	}
}

void System::doCut(int xmin, int ymin, int xmax, int ymax)
{
	if (!shapesManager) 
		return;
	shapesManager->cut(xmin, ymin, xmax, ymax);
}

void System::save(std::string filename)
{
	imageSaver.save(filename);
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
	case CHOOSE:
		return "CHOOSE";
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
	cutWin.setIsCut(isCut);
}

void System::moveFocusPointTo(int x, int y)
{
	if (!isDragable) return;
	if(cutWin.getIsCut())
		cutWin.moveFocusPointTo(x, y);
	else {
		shapesManager->moveFocusPointTo(x, y);
	}
}

void System::clearCurrent()
{
	shapesManager->clearCurrent();
	setIsEditable(true);
}

void System::clearPointStack()
{
	shapesManager->clearPointStack();
}
