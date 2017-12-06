#include "Circle.h"


Circle::Circle(const Point & centre, int radius):
	centre(centre), radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::draw() const
{
	int x_c = 0, y_c = radius;
	float p = (float)5 / 4 - radius;
	for (; abs(x_c - y_c) > 1 ;) {
		if (p < 0) {
			int cur_x = x_c + 1;
			int cur_y = y_c;
			draw8points(cur_x, cur_y);
			p = p + 2 * x_c + 3;
			x_c = x_c + 1;
			// y_c = y_c;
		}
		else {
			int cur_x = x_c + 1;
			int cur_y = y_c - 1;
			draw8points(cur_x, cur_y);
			p = p + 2 * (x_c + 1) + 3 - 2 * y_c - 2;
			x_c = x_c + 1;
			y_c = y_c - 1;
		}
	}
}

void Circle::strongDraw() const
{
	draw();
	glEnd();
	glLineStipple(2, 0x5555);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2i(centre.getX() - radius, centre.getY() - radius);
	glVertex2i(centre.getX() - radius, centre.getY() + radius);
	glVertex2i(centre.getX() - radius, centre.getY() + radius);
	glVertex2i(centre.getX() + radius, centre.getY() + radius);
	glVertex2i(centre.getX() + radius, centre.getY() + radius);
	glVertex2i(centre.getX() + radius, centre.getY() - radius);
	glVertex2i(centre.getX() + radius, centre.getY() - radius);
	glVertex2i(centre.getX() - radius, centre.getY() - radius);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_POINTS);
	//Point(centre.getX() - radius, centre.getY() - radius).strongDraw();
	//Point(centre.getX() - radius, centre.getY() + radius).strongDraw();
	//Point(centre.getX() + radius, centre.getY() - radius).strongDraw();
	//Point(centre.getX() + radius, centre.getY() + radius).strongDraw();
}

void Circle::draw8points(int cur_x, int cur_y) const
{
	pDrawPointFunc(centre.getX() - cur_x, centre.getY() - cur_y);
	pDrawPointFunc(centre.getX() - cur_x, centre.getY() + cur_y);
	pDrawPointFunc(centre.getX() + cur_x, centre.getY() - cur_y); 
	pDrawPointFunc(centre.getX() + cur_x, centre.getY() + cur_y); 
	pDrawPointFunc(centre.getX() - cur_y, centre.getY() - cur_x); 
	pDrawPointFunc(centre.getX() - cur_y, centre.getY() + cur_x); 
	pDrawPointFunc(centre.getX() + cur_y, centre.getY() - cur_x); 
	pDrawPointFunc(centre.getX() + cur_y, centre.getY() + cur_x);
}
