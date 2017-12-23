#include "LinesManager.h"
#include <cmath>
#include "System.h"
#include <memory>

LinesManager::LinesManager()
{
}


LinesManager::~LinesManager()
{
}

void LinesManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::LINE
		&& mySystem->getIsEditable()) {

		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) return;

		for (std::vector<std::shared_ptr<Shape>>::const_iterator
			cit = shapes.begin(); cit != shapes.end() - 1; cit++) {
			(*cit)->draw();
		}
		std::shared_ptr<Shape> line = shapes.back();
		line->strongDraw();
	
	}
	else {
		for (std::shared_ptr<Shape> l : shapes) {
			l->draw();
		}
		if (point_stack.size() < 1) return;

		assert(point_stack.size() == 1);
		Line(point_stack[0], Point(mouseX, mouseY)).draw();
	}
}

void LinesManager::add(const Point & p1, const Point & p2)
{	
	shapes.push_back(std::make_shared<Line>(p1, p2));
}
/*
void LinesManager::clearCurrent()
{
	if (!shapes.empty()) {
		shapes.pop_back();
	}
}
*/
void LinesManager::down(int x, int y)
{
	if (!mySystem->getIsEditable()) {
		point_stack.push_back(Point(x, y));
	}
	else { //is editable
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) {
			mySystem->setIsEditable(false);
			return;
		}
		std::shared_ptr<Shape> line = shapes.back();

		if (line->nearBy(x, y)) {

		}
		else {
			mySystem->setIsEditable(false);
		}
	}
}

void LinesManager::up(int x, int y)
{
	if (point_stack.empty()) return;
	if (!mySystem->getIsEditable()) {
		point_stack.push_back(Point(x, y));
		assert(point_stack.size() == 2);
		Point & start = point_stack[0];
		Point & end = point_stack[1];
		add(start, end);
		point_stack.clear();
		mySystem->setIsEditable(true);
	}
	else {
		//is editable
	}
}

void LinesManager::cut(int xmin, int ymin, int xmax, int ymax)
{
	if (!mySystem->getIsEditable()) return;
	if (shapes.size() <= 0) return;
	assert(point_stack.size() == 0);
	std::shared_ptr<Cutable> cutable = std::dynamic_pointer_cast<Cutable>(shapes.back());
	if (!cutable->cut(xmin, ymin, xmax, ymax))
		shapes.pop_back();
}
