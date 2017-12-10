#include "Ellipise.h"



Ellipise::Ellipise(const Point & centre, int r_x, int r_y):
	centre(centre), r_x(r_x), r_y(r_y),
	editRect(
		centre.getX()-r_x, 
		centre.getY()-r_y,
		centre.getX() + r_x,
		centre.getY() + r_y
		)
{
}

Ellipise::~Ellipise()
{
}

void Ellipise::draw() const
{
	float p1 = r_y * r_y - r_x * r_x * r_y + (float)r_x * r_x / 4;
	int cur_x = 0, cur_y = r_y;
	for (; 2 * pow(r_y) * cur_x < 2 * pow(r_x) * cur_y;) {
		if (p1 < 0) {
			p1 = p1 + 2 * pow(r_y) * cur_x + 3 * pow(r_y);
			cur_x++;
			draw4points(cur_x, cur_y);
			//cur_y = cur_y;
		}
		else { //p1 >= 0
			p1 = p1
				+ 2 * pow(r_y) * cur_x
				- 2 * pow(r_x) * cur_y
				+ 2 * pow(r_x)
				+ 3 * pow(r_y);
			cur_x++;
			cur_y--;
			draw4points(cur_x, cur_y);
		}
	}
	float p2 = pow(r_y) * pow((cur_x + (float)1 / 2))
		+ pow(r_x) * pow(cur_y - 1)
		- pow(r_x) * pow(r_y);
	for (; cur_y >= 0;) {
		if (p2 > 0) {
			p2 = p2 - 2 * pow(r_x) * cur_y + 3 * pow(r_x);
			cur_y--;
			draw4points(cur_x, cur_y);
		}
		else {
			p2 = p2
				+ 2 * pow(r_y) * cur_x
				- 2 * pow(r_x) * cur_y
				+ 2 * pow(r_y)
				+ 3 * pow(r_x);
			cur_x++;
			cur_y--;
			draw4points(cur_x, cur_y);
		}
	}
}

void Ellipise::strongDraw() const
{
	centre.strongDraw();
	draw();
	editRect.strongDraw();
}

void Ellipise::moveFocusPointTo(int x, int y)
{
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
			focus_point->set(x, y);
			editRect.get_lt()->setY(y);
			editRect.get_rb()->setX(x);
		}
		else if (focus_point == editRect.get_rb()) {
			focus_point->set(x, y);
			editRect.get_lb()->setY(y);
			editRect.get_rt()->setX(x);
		}
		else if (focus_point == editRect.get_lt()) {
			focus_point->set(x, y);
			editRect.get_rt()->setY(y);
			editRect.get_lb()->setX(x);
		}
		else if (focus_point == editRect.get_lb()) {
			focus_point->set(x, y);
			editRect.get_rb()->setY(y);
			editRect.get_lt()->setX(x);
		}
		else {
			assert(0);
		}
		int centre_x = (editRect.getLeft() + editRect.getRight()) / 2;
		int centre_y = (editRect.getTop() + editRect.getBottom()) / 2;
		centre.set(centre_x, centre_y);
		r_x = centre_x - editRect.getLeft();
		r_y = centre_y - editRect.getBottom();
	}
}

void Ellipise::translate(int x, int y)
{
	centre.translate(x, y);
	editRect.translate(x, y);
}

void Ellipise::rotate(float angle)
{
	//centre.rotate(angle);
	int tmp = r_x;
	r_x = r_y;
	r_y = tmp;

	editRect.setTop(centre.getY() + r_y);
	editRect.setBottom(centre.getY() - r_y);
	editRect.setLeft(centre.getX() - r_x);
	editRect.setRight(centre.getX() + r_x);
}

void Ellipise::scale(float s1, float s2)
{
	r_x *= s1;
	r_y *= s2;

	editRect.setTop(centre.getY() + r_y);
	editRect.setBottom(centre.getY() - r_y);
	editRect.setLeft(centre.getX() - r_x);
	editRect.setRight(centre.getX() + r_x);
}

bool Ellipise::nearBy(int x, int y)
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

void Ellipise::draw4points(int cur_x, int cur_y) const
{
	pDrawPointFunc(centre.getX() - cur_x, centre.getY() - cur_y);
	pDrawPointFunc(centre.getX() - cur_x, centre.getY() + cur_y);
	pDrawPointFunc(centre.getX() + cur_x, centre.getY() - cur_y);
	pDrawPointFunc(centre.getX() + cur_x, centre.getY() + cur_y);
}
