#pragma once
#include "Shape.h"
#include "Point.h"
#include "Rect.h"

class Ellipise :
	public Shape
{
public:
	Ellipise(const Point & centre, int r_x, int r_y);
	~Ellipise();
	virtual void draw() const override;
	virtual void strongDraw() const override;
	virtual void moveFocusPointTo(int x, int y);
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;
	virtual bool nearBy(int x, int y) override;
protected:
	static float pow(float val) { return val * val; }
	void draw4points(int cur_x, int cur_y) const;
private:
	Point centre;
	int r_x, r_y;
	Rect editRect;
	Point* focus_point;
};

