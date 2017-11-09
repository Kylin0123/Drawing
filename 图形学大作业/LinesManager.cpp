#include "LinesManager.h"



LinesManager::LinesManager()
{
}


LinesManager::~LinesManager()
{
}

void LinesManager::drawAll(int mouseX, int mouseY, bool isEditable) const
{
	for (std::shared_ptr<Line> l : lines)
		l->draw();

	if (point_stack.size() < 1) return;

	if (isEditable) {
		assert(point_stack.size() == 2);
		point_stack[0].strongDraw();
		point_stack[1].strongDraw();
		Line(point_stack[0], point_stack[1]).draw();
	}
	else {
		assert(point_stack.size() == 1);
		Line(point_stack[0], Point(mouseX, mouseY)).draw();
	}
}

void LinesManager::add(const Point & p1, const Point & p2)
{
	lines.push_back(
		std::shared_ptr<Line>(new Line(p1, p2))
	);
}

void LinesManager::down(int x, int y, bool & isEditable, Point* & focus_point)
{
	if (!isEditable)
		point_stack.push_back(Point(x, y));
	else { //is editable
		assert(point_stack.size() == 2);
		Point & start = point_stack[0];
		Point & end = point_stack[1];
		if (start.nearBy(x, y) == true) {
			focus_point = &start;
		}
		else if (end.nearBy(x, y) == true) {
			focus_point = &end;
		}
		else { //click on blank space
			add(start, end);
			point_stack.clear();
			isEditable = false;
		}
	}
}

void LinesManager::up(int x, int y, bool & isEditable)
{
	if (point_stack.empty()) return;
	if (!isEditable) {
		point_stack.push_back(Point(x, y));
		isEditable = true;
	}
	else {
		//is editable
	}
}
