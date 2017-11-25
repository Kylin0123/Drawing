#include "PolygonsManager.h"



PolygonsManager::PolygonsManager():
	isFill(false)
{
}


PolygonsManager::~PolygonsManager()
{
}

void PolygonsManager::add(bool isFill)
{
	polygons.push_back(
		std::shared_ptr<MyPolygon>(new MyPolygon(point_stack))
	);
	if (isFill)
		polygons.back()->fill(windowHeight);
}

void PolygonsManager::setFill(bool isFill)
{
	this->isFill = isFill;
}

void PolygonsManager::drawAll(int mouseX, int mouseY, bool isEditable) const
{
	for (std::shared_ptr<MyPolygon> p : polygons) {
		p->draw();
	}

	if (point_stack.size() < 1) return;

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
}

void PolygonsManager::down(int x, int y, bool & isEditable, Point *& focus_point)
{
	if (!isEditable) {
		static DWORD last_time = 0;
		DWORD time = GetCurrentTime();
		if (time - last_time <= 200) {
			//double click time is shorter than 200 ms
			isEditable = true;
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
			isEditable = false;
			add(isFill);
			point_stack.clear();
		}
	}
}

void PolygonsManager::up(int x, int y, bool & isEditable)
{
}

void PolygonsManager::translate(int x, int y, bool isEditable)
{
	if (!isEditable) return;
	assert(point_stack.size() >= 3);
	int m[3][3] = { { 1,0,x },{ 0,1,y },{ 0,0,1 } };
	Matrix<int> matrix((int*)m, 3, 3);
	for (int i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}

void PolygonsManager::rotate(float angle, bool isEditable)
{
	if (!isEditable) return;
	assert(point_stack.size() >= 3);
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

void PolygonsManager::scale(float s1, float s2, bool isEditable)
{
	if (!isEditable) return;
	assert(point_stack.size() >= 3);
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

