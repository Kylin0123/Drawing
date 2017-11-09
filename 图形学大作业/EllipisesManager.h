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
	void drawAll(int mouseX, int mouseY, bool isEditable) const;
	void add(const Point & p1, const Point & p2);
	void down(int x, int y, bool & isEditable, Point* & focus_point);
	void up(int x, int y, bool & isEditable);
private:
	std::vector<std::shared_ptr<Ellipise> > ellipises;
};

