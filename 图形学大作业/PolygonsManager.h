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
	void add(bool isFill);
	void setFill(bool isFill);
	bool getIsFill() { return isFill; }
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void fillOrNot() override;
	void refill();
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override;
private:
	bool isFill;
};

