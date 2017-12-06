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

void BeziersManager::drawAll(int mouseX, int mouseY) const
{
	for (std::shared_ptr<Bezier> b : beziers) {
		b->draw();
	}
}

void BeziersManager::down(int x, int y, Point *& focus_point)
{
	point_stack.push_back(Point(x, y));
	if (point_stack.size() == bezierNum) {
		add();
		point_stack.clear();
	}
}

void BeziersManager::up(int x, int y)
{
}

void BeziersManager::translate(int x, int y)
{
	/*TODO:no test*/
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == bezierNum);
	int m[3][3] = { { 1,0,x },{ 0,1,y },{ 0,0,1 } };
	Matrix<int> matrix((int*)m, 3, 3);
	for (size_t i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}
}

void BeziersManager::rotate(float angle)
{
	/*TODO:no test*/
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == bezierNum);
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

void BeziersManager::scale(float s1, float s2)
{
	/*TODO:no test*/
	if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == bezierNum);
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
