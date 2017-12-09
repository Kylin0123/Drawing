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
	virtual void down(int x, int y, Point* & focus_point) override;
	virtual void up(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override;
private:
	std::vector<std::shared_ptr<Line> > lines;
};

