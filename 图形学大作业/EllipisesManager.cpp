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
	if (mySystem->getInputType() == System::InputType::ELLIPISE
		&& mySystem->getIsEditable()) {
		//is editable
		assert(point_stack.size() == 0);
		if (ellipises.size() <= 0) return;

		for (std::vector<std::shared_ptr<Ellipise>>::const_iterator
			cit = ellipises.begin(); cit != ellipises.end() - 1; cit++) {
			(*cit)->draw();
		}

		std::shared_ptr<Ellipise> ellipise = ellipises.back();
		ellipise->strongDraw();
	}
	else {
		for (std::shared_ptr<Ellipise> c : ellipises) {
			c->draw();
		}
		if (point_stack.size() != 1) return;		
		
		const Point & p1 = point_stack[0];
		const Point p2(mouseX, mouseY);
		int centre_x = (p1.getX() + p2.getX()) / 2;
		int centre_y = (p1.getY() + p2.getY()) / 2;
		int r_x = abs(centre_x - p1.getX());
		int r_y = abs(centre_y - p1.getY());
		Point centre(centre_x, centre_y);
		Ellipise(centre, r_x, r_y).strongDraw();
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

void EllipisesManager::clearCurrent()
{
	if (!ellipises.empty()) {
		ellipises.pop_back();
	}
}

void EllipisesManager::down(int x, int y)
{
	if (!mySystem->getIsEditable()) {
		assert(point_stack.size() == 0);
		point_stack.push_back(Point(x, y));
	}
	else {
		//is editable
		assert(point_stack.size() == 0);
		if (ellipises.size() <= 0) {
			mySystem->setIsEditable(false);
			return;
		}
		std::shared_ptr<Ellipise> ellipise = ellipises.back();

		if (ellipise->nearBy(x, y)) {
			
		}
		else {
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

void EllipisesManager::moveFocusPointTo(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (ellipises.size() <= 0) return;
	std::shared_ptr<Ellipise> ellipise = ellipises.back();
	ellipise->moveFocusPointTo(x, y);
}

void EllipisesManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (ellipises.size() <= 0) return;
	assert(point_stack.size() == 0);
	ellipises.back()->translate(x, y);
}

void EllipisesManager::rotate(float angle)
{
	if (!mySystem->getIsEditable()) return;
	if (ellipises.size() <= 0) return;
	assert(point_stack.size() == 0);
	ellipises.back()->rotate(angle);
}

void EllipisesManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	if (ellipises.size() <= 0) return;
	assert(point_stack.size() == 0);
	ellipises.back()->scale(s1, s2);
	/*if (!mySystem->getIsEditable()) return;
	assert(point_stack.size() == 2);
	float m[3][3] = {
		{ s1, 0, 0 },
		{ 0, s2, 0 },
		{ 0, 0, 1 }
	};
	Matrix<float> matrix((float*)m, 3, 3);
	for (size_t i = 0; i < point_stack.size(); i++) {
		point_stack[i].change(matrix);
	}*/
}
