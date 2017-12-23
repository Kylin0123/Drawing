#include "BeziersManager.h"
#include "System.h"


BeziersManager::BeziersManager()
{
}


BeziersManager::~BeziersManager()
{
}

void BeziersManager::add()
{
	shapes.push_back(std::make_shared<Bezier>(point_stack));
}
/*
void BeziersManager::clearCurrent()
{
	if (!shapes.empty()) {
		shapes.pop_back();
	}
}
*/
void BeziersManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::BEZIER
		&& mySystem->getIsEditable()) {

		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) return;

		for (std::vector<std::shared_ptr<Shape>>::const_iterator
			cit = shapes.begin(); cit != shapes.end() - 1; cit++) {
			(*cit)->draw();
		}

		std::shared_ptr<Shape> bezier = shapes.back();
		bezier->strongDraw();

	}
	else {
		for (std::shared_ptr<Shape> b : shapes) {
			b->draw();
		}
		if (point_stack.size() < 1) return;

		for (const Point & p : point_stack) {
			p.strongDraw();
		}
	}
}

void BeziersManager::down(int x, int y)
{
	if(!mySystem->getIsEditable()) {
		point_stack.push_back(Point(x, y));
		if (point_stack.size() == bezierNum) {
			add();
			mySystem->setIsEditable(true);
			point_stack.clear();
		}
	}
	else { //is editable
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) {
			mySystem->setIsEditable(false);
			return;
		}
		std::shared_ptr<Shape> bezier = shapes.back();

		if (bezier->nearBy(x, y)) {

		}
		else {
			mySystem->setIsEditable(false);
		}
	}
}

void BeziersManager::up(int x, int y)
{
}