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
	virtual void drawAll(int mouseX, int mouseY, bool isEditable) const override;
	virtual void down(int x, int y, bool & isEditable, Point* & focus_point) override;
	virtual void up(int x, int y, bool & isEditable) override;
	virtual void translate(int x, int y, bool isEditable) override;
	virtual void rotate(float angle, bool isEditable) override;
	virtual void scale(float s1, float s2, bool isEditable) override;
private:
	std::vector<std::shared_ptr<Bezier> > beziers;
	const int bezierNum = 3;
};

