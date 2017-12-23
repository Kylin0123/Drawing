#pragma once
#include <vector>
#include <memory>
#include "Line.h"
#include <cassert>
#include "ShapesManager.h"


class LinesManager : 
	public ShapesManager
{
public:
	LinesManager();
	~LinesManager();
	void add(const Point & p1, const Point & p2);
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void fillOrNot() override {/*NOTE: I don't know how to implement*/ }
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override;
};

