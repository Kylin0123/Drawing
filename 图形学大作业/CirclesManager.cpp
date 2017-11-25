#include "CirclesManager.h"



CirclesManager::CirclesManager()
{
}


CirclesManager::~CirclesManager()
{
}

void CirclesManager::drawAll(int mouseX, int mouseY, bool isEditable) const
{
	for (std::shared_ptr<Circle> c : circles) {
		c->draw();
	}

	if (point_stack.size() < 1) return;

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

void CirclesManager::add(const Point & p1, const Point & p2)
{
	std::tuple<Point, int> ret = caculateCirclePos(p1, p2);
	circles.push_back(
		std::shared_ptr<Circle>(new Circle(std::get<0>(ret), std::get<1>(ret)))
	);
}

void CirclesManager::down(int x, int y, bool & isEditable, Point *& focus_point)
{
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
			add(start, end);
			point_stack.clear();
			isEditable = false;
		}
	}
}

void CirclesManager::up(int x, int y, bool & isEditable)
{
	if (point_stack.empty()) return;
	if (!isEditable) {
		point_stack.push_back(Point(x, y));
		assert(point_stack.size() == 2);
		isEditable = true;
	}
	else {
		//is editable
	}
}

void CirclesManager::translate(int x, int y, bool isEditable)
{
	if (!isEditable) return;
	assert(point_stack.size() == 2);
	int m[3][3] = { { 1,0,x },{ 0,1,y },{ 0,0,1 } };
	Matrix<int> matrix((int*)m, 3, 3);
	for (int i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}

void CirclesManager::rotate(float angle, bool isEditable)
{
	//TODO: wrong rotation
	if (!isEditable) return;
	assert(point_stack.size() == 2);
	float m[3][3] = {
		{ cos(angle), -sin(angle), 0 },
		{ sin(angle), cos(angle), 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	for (int i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}

void CirclesManager::scale(float s1, float s2, bool isEditable)
{
	if (!isEditable) return;
	assert(point_stack.size() == 2);
	float m[3][3] = {
		{ s1, 0, 0 },
		{ 0, s2, 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	for (int i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
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
