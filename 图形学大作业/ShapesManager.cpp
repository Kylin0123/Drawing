#include "ShapesManager.h"

int ShapesManager::windowHeight = 0;
int ShapesManager::windowWidth = 0;

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

void ShapesManager::setWindowSize(int windowWidth, int windowHeight)
{
	ShapesManager::windowWidth = windowWidth;
	ShapesManager::windowHeight = windowHeight;
}
