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
	for (std::shared_ptr<Line> l : lines)
		l->draw();

	if (point_stack.size() < 1) return;

	if (mySystem->getIsEditable()) {
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

void LinesManager::down(int x, int y, Point* & focus_point)
{
	if (!mySystem->getIsEditable()) {
		point_stack.push_back(Point(x, y));
	}
	else { //is editable
		//assert(point_stack.size() == 2);
		if (point_stack.size() != 2) {
			point_stack.clear();
			mySystem->setIsEditable(false);
			return;
		}
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
			mySystem->setIsEditable(false);
		}
	}
}

void LinesManager::up(int x, int y)
{
	if (point_stack.empty()) return;
	if (!mySystem->getIsEditable()) {
		point_stack.push_back(Point(x, y));
		mySystem->setIsEditable(true);
	}
	else {
		//is editable
	}
}

void LinesManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	int m[3][3] = { { 1,0,x },{ 0,1,y },{ 0,0,1 } };
	Matrix<int> matrix((int*)m, 3, 3);
	point_stack[0].change(matrix);
	point_stack[1].change(matrix);
}

void LinesManager::rotate(float angle)
{
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	float m[3][3] = { 
		{cos(angle), -sin(angle), 0},
		{sin(angle), cos(angle), 0},
		{0, 0, 1}
	};
	Matrix<float> matrix((float*)m, 3, 3);
	point_stack[0].change(matrix);
	point_stack[1].change(matrix);
}

void LinesManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	float m[3][3] = {
		{ s1, 0, 0 },
		{ 0, s2, 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	point_stack[0].change(matrix);
	point_stack[1].change(matrix);
}

void LinesManager::cut(int xmin, int ymin, int xmax, int ymax)
{
	if(mySystem->getIsEditable() != true) return;
	if(point_stack.size() != 2) return;
	
	Point p1 = point_stack[0];
	Point p2 = point_stack[1];

	int p[5], q[5];
	float u1 = 0, u2 = 1;
	bool flag = false;
	p[1] = p1.getX() - p2.getX();
	p[2] = p2.getX() - p1.getX();
	p[3] = p1.getY() - p2.getY();
	p[4] = p2.getY() - p1.getY();

	q[1] = p1.getX() - xmin;
	q[2] = xmax - p1.getX();
	q[3] = p1.getY() - ymin;
	q[4] = ymax - p1.getY();

	for (int i = 1; i <= 4; i++) {
		float r = (float)q[i] / p[i];
		if (p[i] < 0) {
			u1 = max(u1, r);
			if (u1 > u2) {
				flag = true;
			}
		} 
		else if (p[i] > 0) {
			u2 = min(u2, r);
			if (u1 > u2) {
				flag = true;
			}
		} 
		else if (p[i] == 0 && q[i] < 0) {
			flag = true;
		}
	}

	if (flag) {
		point_stack.clear();
		return;
	}

	point_stack[0] = Point(p1.getX() + (int)(u1 * (p2.getX() - p1.getX())),
		p1.getY() + (int)(u1 * (p2.getY() - p1.getY())));
	point_stack[1] = Point(p1.getX() + (int)(u2 * (p2.getX() - p1.getX())),
		p1.getY() + (int)(u2 * (p2.getY() - p1.getY())));
}
