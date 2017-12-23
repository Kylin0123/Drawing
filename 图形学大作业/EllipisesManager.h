#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "Ellipise.h"
#include "ShapesManager.h"


class EllipisesManager : 
	public ShapesManager
{
public:
	EllipisesManager();
	~EllipisesManager();
	void add(const Point & p1, const Point & p2);
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void fillOrNot() override {/*TODO: should implement*/}
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override {/*NOTE: I don't know how to implement*/}
};

