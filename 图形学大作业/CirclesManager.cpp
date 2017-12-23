#include "CirclesManager.h"
#include "System.h"


CirclesManager::CirclesManager()
{
}


CirclesManager::~CirclesManager()
{
}

void CirclesManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::CIRCLE
		&& mySystem->getIsEditable()) {
		//is editable
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) return;

		for (std::vector<std::shared_ptr<Shape>>::const_iterator
			cit = shapes.begin(); cit != shapes.end() - 1; cit++) {
			(*cit)->draw();
		}

		std::shared_ptr<Shape> circle = shapes.back();
		circle->strongDraw();
	}
	else {
		for (std::shared_ptr<Shape> c : shapes) {
			c->draw();
		}
		if (point_stack.size() != 1) return;
		std::tuple<Point, int> ret = caculateCirclePos(point_stack[0], Point(mouseX, mouseY));
		Circle(std::get<0>(ret), std::get<1>(ret)).strongDraw();
	}
}

void CirclesManager::add(const Point & p1, const Point & p2)
{
	std::tuple<Point, int> ret = caculateCirclePos(p1, p2);
	shapes.push_back(
		std::shared_ptr<Circle>(new Circle(std::get<0>(ret), std::get<1>(ret)))
	);
}
/*
void CirclesManager::clearCurrent()
{
	if (!shapes.empty()) {
		shapes.pop_back();
	}
}
*/
void CirclesManager::down(int x, int y)
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
		std::shared_ptr<Shape> circle = shapes.back();

		if (circle->nearBy(x, y)) {

		}
		else {
			mySystem->setIsEditable(false);
		}
	}
}

void CirclesManager::up(int x, int y)
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

std::tuple<Point, int> CirclesManager::caculateCirclePos(const Point & start, const Point & end) const
{
	int delta_x = end.getX() - start.getX();
	int delta_y = end.getY() - start.getY();
	if (abs(delta_x) > abs(delta_y)) {
		int dy = delta_y / 2;
		int dx = delta_x > 0 ? abs(dy) : -abs(dy);
		return std::make_tuple(Point(start.getX() + dx, start.getY() + dy), abs(dy));
	}
	else {
		int offset = delta_y > 0 ? delta_x / 2 : -delta_x / 2;
		int offset2 = delta_x > 0 ? offset : -offset;
		return std::make_tuple(Point(start.getX() + delta_x / 2, start.getY() + offset2), abs(delta_x / 2));
	}
}
