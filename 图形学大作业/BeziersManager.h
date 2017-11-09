#pragma once
#include <vector>
#include <memory>
#include "Bezier.h"
#include "ShapesManager.h"

class BeziersManager :
	public ShapesManager
{
public:
	BeziersManager();
	~BeziersManager();
	void drawAll(int mouseX, int mouseY, bool isEditable) const;
	void add();
	void down(int x, int y, bool & isEditable, Point* & focus_point);
	void up(int x, int y, bool & isEditable);
private:
	std::vector<std::shared_ptr<Bezier> > beziers;
	const int bezierNum = 3;
};

