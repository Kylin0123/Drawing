#include "Circle.h"


Circle::Circle(const Point & centre, int radius):
	centre(centre), radius(radius), focus_point(nullptr),
	editRect(centre.getX()-radius, centre.getY()-radius,
		centre.getX() + radius, centre.getY() + radius)
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
	centre.strongDraw();
	draw();
	editRect.strongDraw();
}

void Circle::moveFocusPointTo(int x, int y)
{
	if (focus_point == nullptr) return;
	if (focus_point == &centre) {
		int dx = x - centre.getX();
		int dy = y - centre.getY();
		centre.set(x, y);
		editRect.translate(dx, dy);
	}
	else {
		int x0 = focus_point->getX();
		int y0 = focus_point->getY();
		if (focus_point == editRect.get_rt()) {
			int dx = x - x0;
			int dy = y - y0;
			int d = dx >= dy ? dy : dx;
			focus_point->set(x0 + d, y0 + d);
			editRect.get_lt()->setY(y0 + d);
			editRect.get_rb()->setX(x0 + d);
		}
		else if (focus_point == editRect.get_rb()) {
			int dx = x - x0;
			int dy = y0 - y;
			int d = dx >= dy ? dy : dx;
			focus_point->set(x0 + d, y0 - d);
			editRect.get_lb()->setY(y0 - d);
			editRect.get_rt()->setX(x0 + d);
		}
		else if (focus_point == editRect.get_lt()) {
			int dx = x0 - x;
			int dy = y - y0;
			int d = dx >= dy ? dy : dx;
			focus_point->set(x0 - d, y0 + d);
			editRect.get_rt()->setY(y0 + d);
			editRect.get_lb()->setX(x0 - d);
		}
		else if (focus_point == editRect.get_lb()) {
			int dx = x0 - x;
			int dy = y0 - y;
			int d = dx >= dy ? dy : dx;
			focus_point->set(x0 - d, y0 - d);
			editRect.get_rb()->setY(y0 - d);
			editRect.get_lt()->setX(x0 - d);
		}
		else {
			assert(0);
		}
		int centre_x = (editRect.getLeft() + editRect.getRight()) / 2;
		int centre_y = (editRect.getTop() + editRect.getBottom()) / 2;
		centre.set(centre_x, centre_y);
		radius = centre_x - editRect.getLeft();
	}
}

void Circle::translate(int x, int y)
{
	centre.translate(x, y);
	editRect.translate(x, y);
}

void Circle::rotate(float angle)
{
	//nothing I can do
}

void Circle::scale(float s1, float s2)
{
	float min = s1 < s2 ? s1 : s2;
	radius *= min;

	editRect.setTop(centre.getY() + radius);
	editRect.setBottom(centre.getY() - radius);
	editRect.setLeft(centre.getX() - radius);
	editRect.setRight(centre.getX() + radius);
}

bool Circle::nearBy(int x, int y)
{
	if (centre.nearBy(x, y)) {
		focus_point = &centre;
		return true;
	}
	else if (focus_point = editRect.nearBy(x, y)) {
		return true;
	}
	return false;
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
