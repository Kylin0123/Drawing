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
	virtual void clearCurrent() override;
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual void fillOrNot() override;
	void refill();
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override;
private:
	std::vector<std::shared_ptr<MyPolygon> > polygons;
	bool isFill;
};

