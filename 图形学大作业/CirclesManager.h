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
	void add(const Point & p1, const Point & p2);
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y, Point* & focus_point) override;
	virtual void up(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
protected:
	std::tuple<Point, int> caculateCirclePos(const Point & start, const Point & end) const;
private:
	std::vector<std::shared_ptr<Circle> > circles;
};

