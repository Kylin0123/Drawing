#pragma once
#include <vector>
#include <memory>
#include "Bezier.h"
#include <cassert>
#include "ShapesManager.h"

class BeziersManager :
	public ShapesManager
{
public:
	BeziersManager();
	~BeziersManager();
	void add();
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void fillOrNot() override {/*NOTE: I don't know how to implement*/}
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override {/*NOTE: for the future extense*/}
private:
	const int bezierNum = 4;
};

