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
	virtual void down(int x, int y, Point* & focus_point) override;
	virtual void up(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
private:
	std::vector<std::shared_ptr<Bezier> > beziers;
	const int bezierNum = 3;
};

