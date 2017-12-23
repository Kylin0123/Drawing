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

void ShapesManager::clearCurrent()
{
	if (!shapes.empty()) {
		shapes.pop_back();
	}
}

void ShapesManager::clearPointStack()
{
	point_stack.clear();
}

void ShapesManager::setSystem(System * system)
{
	mySystem = system;
}

bool ShapesManager::nearBy(int x, int y)
{
	for (std::vector<std::shared_ptr<Shape>>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		if ((*it)->nearBy(x, y)) {
			const std::shared_ptr<Shape> shape = *it;
			shapes.erase(it);
			shapes.push_back(shape);
			return true;
		}
	}
	return false;
}

void ShapesManager::moveFocusPointTo(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (shapes.size() <= 0) return;
	std::shared_ptr<Shape> shape = shapes.back();
	shape->moveFocusPointTo(x, y);
}

void ShapesManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (shapes.size() <= 0) return;
	assert(point_stack.size() == 0);
	shapes.back()->translate(x, y);
}

void ShapesManager::rotate(float angle)
{
	if (!mySystem->getIsEditable()) return;
	if (shapes.size() <= 0) return;
	assert(point_stack.size() == 0);
	shapes.back()->rotate(angle);
}

void ShapesManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	if (shapes.size() <= 0) return;
	assert(point_stack.size() == 0);
	shapes.back()->scale(s1, s2);
}
