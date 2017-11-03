#include "System.h"
#include <cassert>
#include <tuple>

System::System():
	inputType(LINE), bezierNum(3), isEditable(false)
{
}


System::~System()
{
}

void System::draw()
{
	for (auto & p : points) {
		p->draw();
	}
	for (auto & l : lines) {
		l->draw();
	}
	for (auto & b : beziers) {
		b->draw();
	}
	for (auto & p : polygons) {
		p->draw();
	}
	for (auto & c : circles) {
		c->draw();
	}

	if (point_stack.size() < 1) return;

	switch (inputType) {
	case LINE:
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
		break;
	case BEZIER:
		break;
	case POLYGON:
		if (isEditable) {
			assert(point_stack.size() >= 3);
			for (int i = 0; i < point_stack.size() - 1; i++) {
				point_stack[i].strongDraw();
				Line(point_stack[i], point_stack[i + 1]).draw();
			}
			point_stack.back().strongDraw();
			Line(point_stack.back(), point_stack.front()).draw();
		}
		else {
			for (int i = 0; i < point_stack.size() - 1; i++) {
				Line(point_stack[i], point_stack[i + 1]).draw();
			}
			Line(point_stack.back(), Point(mouseX, mouseY)).draw();
		}
		break;
	case CIRCLE: {
		if (isEditable) {
			assert(point_stack.size() == 2);
			std::tuple<Point, int> ret = caculateCirclePos(point_stack[0], point_stack[1]);
			Circle(std::get<0>(ret), std::get<1>(ret)).draw();
			point_stack[0].strongDraw();
			point_stack[1].strongDraw();
		}
		else {
			std::tuple<Point, int> ret = caculateCirclePos(point_stack[0], Point(mouseX, mouseY));
			Circle(std::get<0>(ret), std::get<1>(ret)).draw();
		}
	}
		break;
	case ELLIPSE:
		break;
	case FILL:
		break;
	default:
		assert(0);
	}
}

void System::down(int x, int y)
{
	switch (inputType) {
	case LINE: 
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
				addLine(start, end);
				point_stack.clear();
				setIsEditable(false);
			}
		}
		break;
	case BEZIER:
		point_stack.push_back(Point(x, y));
		if (point_stack.size() >= bezierNum) {
			addBezier();
			point_stack.clear();
		}
		break;
	case POLYGON: {
		if (!isEditable) {
			static DWORD last_time = 0;
			DWORD time = GetCurrentTime();
			if (time - last_time <= 200) {
				//double click time is shorter than 200 ms
				setIsEditable(true);
			}
			else
				point_stack.push_back(Point(x, y));
			last_time = time;
		}
		else { // is editable
			bool flag = false;
			for (int i = 0; i < point_stack.size(); i++) {
				if (point_stack[i].nearBy(x, y)) {
					focus_point = &point_stack[i];
					flag = true;
				}
			}
			if (!flag) {
				setIsEditable(false);
				addMyPolygon();
				point_stack.clear();
			}
		}
		break;
	}
	case CIRCLE: {
		if (!isEditable) {
			assert(point_stack.size() == 0);
			point_stack.push_back(Point(x, y));
		}
		else {
			assert(point_stack.size() == 2);
			Point & start = point_stack[0];
			Point & end = point_stack[1];
			if (start.nearBy(x, y)) {
				focus_point = &start;
			}
			else if (end.nearBy(x, y)) {
				focus_point = &end;
			}
			else {
				addCircle(start, end);
				point_stack.clear();
				setIsEditable(false);
			}
		}
	}
		break;
	case ELLIPSE:
		break;
	case FILL:
		break;
	default:
		assert(0);
	}
}

void System::up(int x, int y)
{
	switch (inputType) {
	case LINE:
		if (point_stack.empty()) return;
		if (!isEditable) {
			point_stack.push_back(Point(x, y));
			setIsEditable(true);
		}
		else {
			//is editable
		}
		break;
	case CIRCLE:
		if (point_stack.empty()) return;
		if (!isEditable) {
			point_stack.push_back(Point(x, y));
			assert(point_stack.size() == 2);
			setIsEditable(true);
		}
		else {
			//is editable
		}
		break;
	default:
		break;
	}
}

void System::addPoint(int x, int y)
{
	points.push_back(
		std::shared_ptr<Point>(new Point(x,y))
	);
}

void System::addLine(const Point & p1, const Point & p2)
{
	lines.push_back(
		std::shared_ptr<Line>(new Line(p1, p2))
	);
}

void System::addBezier()
{
	beziers.push_back(
		std::shared_ptr<Bezier>(new Bezier(point_stack))
	);
}

void System::addMyPolygon()
{
	polygons.push_back(
		std::shared_ptr<MyPolygon>(new MyPolygon(point_stack))
	);
}

void System::addCircle(const Point & p1, const Point & p2)
{
	std::tuple<Point,int> ret = caculateCirclePos(p1, p2);
	circles.push_back(
		std::shared_ptr<Circle>(new Circle(std::get<0>(ret), std::get<1>(ret)))
	);
}

void System::setInputType(InputType inputType)
{
	this->inputType = inputType;
}

System::InputType System::getInputType() const
{
	return inputType;
}

void System::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}

void System::setMousePos(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void System::setIsEditable(bool isEditable)
{
	this->isEditable = isEditable;
}

std::string System::getInputTypeString() {
	switch (inputType) {
	case LINE: return "LINE";
	case BEZIER: return "BEZIER";
	case POLYGON: return "POLYGON";
	case CIRCLE: return "CIRCLE";
	case ELLIPSE: return "ELLIPSE";
	case FILL: return "FILL";
	default: assert(0);
	}
}

void System::setDrawPointFunc(PDrawPointFunc pDrawPointFunc) {
	this->pDrawPointFunc = pDrawPointFunc;
	Shape::pDrawPointFunc = pDrawPointFunc;
}

void System::moveFocusPointTo(int x, int y)
{
	assert(focus_point != nullptr);
	focus_point->set(x, y);
}

void System::clearPointStack()
{
	point_stack.clear();
}

std::tuple<Point, int> System::caculateCirclePos(const Point & start, const Point & end)
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
