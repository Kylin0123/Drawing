#pragma once
#include <vector>
#include <memory>
#include "MyPolygon.h"
#include <cassert>
#include "Line.h"
#include "ShapesManager.h"


class PolygonsManager : 
	public ShapesManager
{
public:
	PolygonsManager();
	~PolygonsManager();
	void drawAll(int mouseX, int mouseY, bool isEditable) const;
	void add(bool isFill);
	void down(int x, int y, bool & isEditable, Point* & focus_point);
	void up(int x, int y, bool & isEditable);
	void setFill(bool isFill);
private:
	std::vector<std::shared_ptr<MyPolygon> > polygons;
	bool isFill;
};

