#pragma once
#include "Shape.h"
#include "Point.h"
class Ellipise :
	public Shape
{
public:
	Ellipise(const Point & centre, int r_x, int r_y);
	~Ellipise();
	virtual void draw() const override;
protected:
	static float pow(float val) { return val * val; }
	void draw4points(int cur_x, int cur_y) const;
private:
	Point centre;
	int r_x, r_y;
};

