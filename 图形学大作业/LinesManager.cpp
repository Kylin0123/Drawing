#include "LinesManager.h"
#include <cmath>
#include "System.h"

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
		if (lines.size() <= 0) return;

		for (std::vector<std::shared_ptr<Line>>::const_iterator
			cit = lines.begin(); cit != lines.end() - 1; cit++) {
			(*cit)->draw();
		}
		
		std::shared_ptr<Line> myPolygon = lines.back();
		myPolygon->strongDraw();
	
	}
	else {
		for (std::shared_ptr<Line> l : lines) {
			l->draw();
		}
		if (point_stack.size() < 1) return;

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

void LinesManager::clearCurrent()
{
	if (!lines.empty()) {
		lines.pop_back();
	}
}

void LinesManager::down(int x, int y)
{
	if (!mySystem->getIsEditable()) {
		point_stack.push_back(Point(x, y));
	}
	else { //is editable
		assert(point_stack.size() == 0);
		if (lines.size() <= 0) {
			mySystem->setIsEditable(false);
			return;
		}
		std::shared_ptr<Line> line = lines.back();

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

void LinesManager::moveFocusPointTo(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (lines.size() <= 0) return;
	std::shared_ptr<Line> line = lines.back();
	line->moveFocusPointTo(x, y);
}

void LinesManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (lines.size() <= 0) return;
	assert(point_stack.size() == 0);
	lines.back()->translate(x, y);
}

void LinesManager::rotate(float angle)
{
	if (!mySystem->getIsEditable()) return;
	if (lines.size() <= 0) return;
	assert(point_stack.size() == 0);
	lines.back()->rotate(angle);
}

void LinesManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	if (lines.size() <= 0) return;
	assert(point_stack.size() == 0);
	lines.back()->scale(s1, s2);
}

void LinesManager::cut(int xmin, int ymin, int xmax, int ymax)
{
	if (!mySystem->getIsEditable()) return;
	if (lines.size() <= 0) return;
	assert(point_stack.size() == 0);
	if (!lines.back()->cut(xmin, ymin, xmax, ymax))
		lines.pop_back();
}
