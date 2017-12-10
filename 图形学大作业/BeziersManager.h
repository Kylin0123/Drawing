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
	virtual void clearCurrent() override;
	virtual void drawAll(int mouseX, int mouseY) const override;
	virtual void down(int x, int y) override;
	virtual void up(int x, int y) override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual void fillOrNot() override {/*NOTE: I don't know how to implement*/}
	virtual void cut(int xmin, int ymin, int xmax, int ymax) override {/*NOTE: for the future extense*/}
private:
	std::vector<std::shared_ptr<Bezier> > beziers;
	const int bezierNum = 3;
};

