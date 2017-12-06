#include "ShapesManager.h"
#include <cassert>

int ShapesManager::windowHeight = 0;
int ShapesManager::windowWidth = 0;
System* ShapesManager::mySystem = nullptr;

ShapesManager::ShapesManager()
{
}


ShapesManager::~ShapesManager()
{
}

void ShapesManager::clearPointStack()
{
	point_stack.clear();
}

void ShapesManager::fillOrNot()
{
	//TODO
	assert(0);
}

void ShapesManager::cut(int x1, int y1, int x2, int y2)
{
	//TODO
	assert(0);
}

void ShapesManager::setWindowSize(int windowWidth, int windowHeight)
{
	ShapesManager::windowWidth = windowWidth;
	ShapesManager::windowHeight = windowHeight;
}

void ShapesManager::setSystem(System * system)
{
	mySystem = system;
}
