#include "EllipisesManager.h"
#include "System.h"


EllipisesManager::EllipisesManager()
{
}


EllipisesManager::~EllipisesManager()
{
}

void EllipisesManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::ELLIPISE
		&& mySystem->getIsEditable()) {
		//is editable
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) return;

		for (std::vector<std::shared_ptr<Shape>>::const_iterator
			cit = shapes.begin(); cit != shapes.end() - 1; cit++) {
			(*cit)->draw();
		}

		std::shared_ptr<Shape> ellipise = shapes.back();
		ellipise->strongDraw();
	}
	else {
		for (std::shared_ptr<Shape> c : shapes) {
			c->draw();
		}
		if (point_stack.size() != 1) return;		
		
		const Point & p1 = point_stack[0];
		const Point p2(mouseX, mouseY);
		int centre_x = (p1.getX() + p2.getX()) / 2;
		int centre_y = (p1.getY() + p2.getY()) / 2;
		int r_x = abs(centre_x - p1.getX());
		int r_y = abs(centre_y - p1.getY());
		Point centre(centre_x, centre_y);
		Ellipise(centre, r_x, r_y).strongDraw();
	}
}

void EllipisesManager::add(const Point & p1, const Point & p2)
{
	int centre_x = (p1.getX() + p2.getX()) / 2;
	int centre_y = (p1.getY() + p2.getY()) / 2;
	int r_x = abs(centre_x - p1.getX());
	int r_y = abs(centre_y - p1.getY());
	Point centre(centre_x, centre_y);
	shapes.push_back(
		std::shared_ptr<Shape>(new Ellipise(centre, r_x, r_y))
	);
}
/*
void EllipisesManager::clearCurrent()
{
	if (!shapes.empty()) {
		shapes.pop_back();
	}
}
*/
void EllipisesManager::down(int x, int y)
{
	if (!mySystem->getIsEditable()) {
		assert(point_stack.size() == 0);
		point_stack.push_back(Point(x, y));
	}
	else {
		//is editable
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) {
			mySystem->setIsEditable(false);
			return;
		}
		std::shared_ptr<Shape> ellipise = shapes.back();

		if (ellipise->nearBy(x, y)) {
			
		}
		else {
			mySystem->setIsEditable(false);
		}
	}
}

void EllipisesManager::up(int x, int y)
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