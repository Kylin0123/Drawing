#include "ShapesManager.h"
#include <cassert>
#include "System.h"

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