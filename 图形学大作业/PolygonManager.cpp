#include "PolygonsManager.h"
#include "System.h"


PolygonsManager::PolygonsManager():
	isFill(false)
{
}


PolygonsManager::~PolygonsManager()
{
}

void PolygonsManager::add(bool isFill)
{
	shapes.push_back(
		std::shared_ptr<Shape>(new MyPolygon(point_stack))
	);
	if (isFill) {
		std::shared_ptr<MyPolygon> back = std::dynamic_pointer_cast<MyPolygon>(shapes.back());
		back->fill();
	}
}

void PolygonsManager::setFill(bool isFill)
{
	this->isFill = isFill;
}
/*
void PolygonsManager::clearCurrent()
{
	if (!shapes.empty()) {
		shapes.pop_back();
	}
}
*/
void PolygonsManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::POLYGON 
		&& mySystem->getIsEditable()) {
		
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) return;
		
		for (std::vector<std::shared_ptr<Shape>>::const_iterator
			cit = shapes.begin(); cit != shapes.end() - 1; cit++) {
			(*cit)->draw();
		}
		/*多边形数组中最后一个多边形是当前指向的多边形*/
		std::shared_ptr<Shape> myPolygon = shapes.back();
		myPolygon->strongDraw();
	}
	else {
		for (std::shared_ptr<Shape> p : shapes) {
			p->draw();
		}
		if (point_stack.size() < 1) return;
		for (size_t i = 0; i < point_stack.size() - 1; i++) {
			Line(point_stack[i], point_stack[i + 1]).draw();
		}
		Line(point_stack.back(), Point(mouseX, mouseY)).draw();
	}
}

void PolygonsManager::down(int x, int y)
{
	if (!mySystem->getIsEditable()) {
		static DWORD last_time = 0;
		DWORD time = GetCurrentTime();
		if (time - last_time <= 200) {
			//double click time is shorter than 200 ms
			//put the current polygon into vector

			add(isFill);
			isFill = false;
			point_stack.clear();
			
			mySystem->setIsEditable(true);
			
		}
		else
			point_stack.push_back(Point(x, y));
		last_time = time;
	}
	else { // is editable
		assert(point_stack.size() == 0);
		if (shapes.size() <= 0) { 
			mySystem->setIsEditable(false);
			return; 
		}
		std::shared_ptr<Shape> myPolygon = shapes.back();

		if (myPolygon->nearBy(x, y)) {

		}
		else {
			mySystem->setIsEditable(false);
			isFill = false;
		}
	}
}

void PolygonsManager::up(int x, int y)
{
}

void PolygonsManager::fillOrNot()
{
	isFill = !isFill;
	std::shared_ptr<MyPolygon> back = std::dynamic_pointer_cast<MyPolygon>(shapes.back());
	if (isFill)
		back->fill();
	else
		back->unfill();
}

void PolygonsManager::refill()
{
	std::shared_ptr<MyPolygon> back = std::dynamic_pointer_cast<MyPolygon>(shapes.back());
	back->refill();
}

void PolygonsManager::cut(int xmin, int ymin, int xmax, int ymax)
{
	if (shapes.size() <= 0) return;
	std::shared_ptr<Cutable> back = std::dynamic_pointer_cast<Cutable>(shapes.back());
	if(!back->cut(xmin, ymin, xmax, ymax))
		shapes.pop_back();
}

