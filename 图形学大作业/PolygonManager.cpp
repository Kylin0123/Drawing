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
	polygons.push_back(
		std::shared_ptr<MyPolygon>(new MyPolygon(point_stack))
	);
	if (isFill)
		polygons.back()->fill(mySystem->getWindowSizeY());
}

void PolygonsManager::setFill(bool isFill)
{
	this->isFill = isFill;
}

void PolygonsManager::drawAll(int mouseX, int mouseY) const
{
	if (mySystem->getInputType() == System::InputType::POLYGON 
		&& mySystem->getIsEditable()) {
		
		assert(point_stack.size() == 0);
		if (polygons.size() <= 0) return;
		
		for (std::vector<std::shared_ptr<MyPolygon>>::const_iterator p = polygons.begin(); p != polygons.end() - 1; p++) {
			(*p)->draw();
		}
		/*多边形数组中最后一个多边形是当前指向的多边形*/
		std::shared_ptr<MyPolygon> myPolygon = polygons.back();
		myPolygon->strongDraw();
	}
	else {
		for (std::shared_ptr<MyPolygon> p : polygons) {
			p->draw();
		}
		if (point_stack.size() < 1) return;
		for (size_t i = 0; i < point_stack.size() - 1; i++) {
			Line(point_stack[i], point_stack[i + 1]).draw();
		}
		Line(point_stack.back(), Point(mouseX, mouseY)).draw();
	}
}

void PolygonsManager::down(int x, int y, Point *& focus_point)
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
		if (polygons.size() <= 0) { 
			mySystem->setIsEditable(false);
			return; 
		}
		bool flag = false;
		std::shared_ptr<MyPolygon> myPolygon = polygons.back();
		for (Point & p : myPolygon->getPointVector()) {
			if (p.nearBy(x, y)) {
				focus_point = &p;
				flag = true;
			}
		}
		if (!flag) {
			mySystem->setIsEditable(false);
			isFill = false;
			point_stack.clear();
		}
	}
}

void PolygonsManager::up(int x, int y)
{
}

void PolygonsManager::translate(int x, int y)
{
	if (!mySystem->getIsEditable()) return;
	if (polygons.size() <= 0) return;
	assert(point_stack.size() == 0);
	polygons.back()->translate(x, y);
}

void PolygonsManager::rotate(float angle)
{
	if (!mySystem->getIsEditable()) return;
	if (polygons.size() <= 0) return;
	assert(point_stack.size() == 0);
	polygons.back()->rotate(angle);
}

void PolygonsManager::scale(float s1, float s2)
{
	if (!mySystem->getIsEditable()) return;
	if (polygons.size() <= 0) return;
	assert(point_stack.size() == 0);
	polygons.back()->scale(s1, s2);
}

void PolygonsManager::fillOrNot()
{
	isFill = !isFill;
	std::shared_ptr<MyPolygon> myPolygon = polygons.back();
	if (isFill)
		myPolygon->fill(mySystem->getWindowSizeY());
	else
		myPolygon->unfill();
}

void PolygonsManager::refill()
{
	std::shared_ptr<MyPolygon> myPolygon = polygons.back();
	myPolygon->unfill();
	myPolygon->fill(mySystem->getWindowSizeY());
}

void PolygonsManager::cut(int xmin, int ymin, int xmax, int ymax)
{
	if (polygons.size() <= 0) return;
	std::shared_ptr<MyPolygon> myPolygon = polygons.back();
	try {
		MyPolygon ret = myPolygon->cut(xmin, ymin, xmax, ymax);
		polygons.back() = std::shared_ptr<MyPolygon>(new MyPolygon(ret));
	}
	catch (std::exception e) {
		polygons.pop_back();
	}

}

