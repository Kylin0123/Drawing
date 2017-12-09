#include "ShapesManager.h"
#include <cassert>

//int ShapesManager::windowHeight = 0;
//int ShapesManager::windowWidth = 0;
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

void ShapesManager::setSystem(System * system)
{
	mySystem = system;
}
