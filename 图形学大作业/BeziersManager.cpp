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
	beziers.push_back(
		std::shared_ptr<Bezier>(new Bezier(point_stack))
	);
}

void BeziersManager::clearCurrent()
{
	if (!beziers.empty()) {
		beziers.pop_back();
	}
}

void BeziersManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::BEZIER
		&& mySystem->getIsEditable()) {

		assert(point_stack.size() == 0);
		if (beziers.size() <= 0) return;

		for (std::vector<std::shared_ptr<Bezier>>::const_iterator
			cit = beziers.begin(); cit != beziers.end() - 1; cit++) {
			(*cit)->draw();
		}

		std::shared_ptr<Bezier> bezier = beziers.back();
		bezier->strongDraw();

	}
	else {
		for (std::shared_ptr<Bezier> b : beziers) {
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
		if (beziers.size() <= 0) {
			mySystem->setIsEditable(false);
			return;
		}
		std::shared_ptr<Bezier> bezier = beziers.back();

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

void BeziersManager::moveFocusPointTo(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (beziers.size() <= 0) return;
	std::shared_ptr<Bezier> bezier = beziers.back();
	bezier->moveFocusPointTo(x, y);
}

void BeziersManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (beziers.size() <= 0) return;
	assert(point_stack.size() == 0);
	beziers.back()->translate(x, y);
}

void BeziersManager::rotate(float angle)
{
	if (!mySystem->getIsEditable()) return;
	if (beziers.size() <= 0) return;
	assert(point_stack.size() == 0);
	beziers.back()->rotate(angle);
}

void BeziersManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	if (beziers.size() <= 0) return;
	assert(point_stack.size() == 0);
	beziers.back()->scale(s1, s2);
}
