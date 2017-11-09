#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include <tuple>
#include "Circle.h"
#include "ShapesManager.h"

class CirclesManager :
	public ShapesManager
{
public:
	CirclesManager();
	~CirclesManager();
	void drawAll(int mouseX, int mouseY, bool isEditable) const;
	void add(const Point & p1, const Point & p2);
	void down(int x, int y, bool & isEditable, Point* & focus_point);
	void up(int x, int y, bool & isEditable);
protected:
	std::tuple<Point, int> caculateCirclePos(const Point & start, const Point & end) const;
private:
	std::vector<std::shared_ptr<Circle> > circles;
};

