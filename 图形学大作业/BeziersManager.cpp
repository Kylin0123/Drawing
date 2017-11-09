#include "BeziersManager.h"



BeziersManager::BeziersManager()
{
}


BeziersManager::~BeziersManager()
{
}

void BeziersManager::drawAll(int mouseX, int mouseY, bool isEditable) const
{
	for (std::shared_ptr<Bezier> b : beziers) {
		b->draw();
	}
}

void BeziersManager::add()
{
	beziers.push_back(
		std::shared_ptr<Bezier>(new Bezier(point_stack))
	);
}

void BeziersManager::down(int x, int y, bool & isEditable, Point *& focus_point)
{
	point_stack.push_back(Point(x, y));
	if (point_stack.size() >= bezierNum) {
		add();
		point_stack.clear();
	}
}

void BeziersManager::up(int x, int y, bool & isEditable)
{
}
