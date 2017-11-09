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
	void drawAll(int mouseX, int mouseY, bool isEditable) const;
	void add(const Point & p1, const Point & p2);
	void down(int x, int y, bool & isEditable, Point* & focus_point);
	void up(int x, int y, bool & isEditable);
private:
	std::vector<std::shared_ptr<Line> > lines;
};

