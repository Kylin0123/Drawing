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
	virtual void clearCurrent() override;
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual void fillOrNot() override {/*TODO: should implement*/}
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override {/*NOTE: I don't know how to do*/}
protected:
	std::tuple<Point, int> caculateCirclePos(const Point & start, const Point & end) const;
private:
	std::vector<std::shared_ptr<Circle> > circles;
};

