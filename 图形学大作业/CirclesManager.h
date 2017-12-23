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
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void fillOrNot() override {/*TODO: should implement*/}
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override {/*NOTE: I don't know how to do*/}
protected:
	std::tuple<Point, int> caculateCirclePos(const Point & start, const Point & end) const;
};

