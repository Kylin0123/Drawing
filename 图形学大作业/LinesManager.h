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
	virtual void translate(int x, int y, bool isEditable) override;
	virtual void rotate(float angle, bool isEditable) override;
	virtual void scale(float s1, float s2, bool isEditable) override;
private:
	std::vector<std::shared_ptr<Line> > lines;
};

