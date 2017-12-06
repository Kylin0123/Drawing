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
	for (std::shared_ptr<Ellipise> e : ellipises) {
		e->draw();
	}

	if (point_stack.size() < 1) return;

	if (mySystem->getIsEditable()) {
		assert(point_stack.size() == 2);
		const Point & p1 = point_stack[0];
		const Point & p2 = point_stack[1];
		p1.strongDraw();
		p2.strongDraw();
		int centre_x = (p1.getX() + p2.getX()) / 2;
		int centre_y = (p1.getY() + p2.getY()) / 2;
		int r_x = abs(centre_x - p1.getX());
		int r_y = abs(centre_y - p1.getY());
		Point centre(centre_x, centre_y);
		Ellipise(centre, r_x, r_y).draw();
	}
	else {
		const Point & p1 = point_stack[0];
		const Point p2(mouseX, mouseY);
		int centre_x = (p1.getX() + p2.getX()) / 2;
		int centre_y = (p1.getY() + p2.getY()) / 2;
		int r_x = abs(centre_x - p1.getX());
		int r_y = abs(centre_y - p1.getY());
		Point centre(centre_x, centre_y);
		Ellipise(centre, r_x, r_y).draw();
	}
}

void EllipisesManager::add(const Point & p1, const Point & p2)
{
	int centre_x = (p1.getX() + p2.getX()) / 2;
	int centre_y = (p1.getY() + p2.getY()) / 2;
	int r_x = abs(centre_x - p1.getX());
	int r_y = abs(centre_y - p1.getY());
	Point centre(centre_x, centre_y);
	ellipises.push_back(
		std::shared_ptr<Ellipise>(new Ellipise(centre, r_x, r_y))
	);
}

void EllipisesManager::down(int x, int y, Point *& focus_point)
{
	if (!mySystem->getIsEditable()) {
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
		mySystem->setIsEditable(true);
	}
	else {
		//is editable
	}
}

void EllipisesManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	int m[3][3] = { { 1,0,x },{ 0,1,y },{ 0,0,1 } };
	Matrix<int> matrix((int*)m, 3, 3);
	for (size_t i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}

void EllipisesManager::rotate(float angle)
{
	//TODO: wrong rotation
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	float m[3][3] = {
		{ cos(angle), -sin(angle), 0 },
		{ sin(angle), cos(angle), 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	for (size_t i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}

void EllipisesManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	float m[3][3] = {
		{ s1, 0, 0 },
		{ 0, s2, 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	for (size_t i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}
