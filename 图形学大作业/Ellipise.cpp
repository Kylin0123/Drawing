#include "Ellipise.h"



Ellipise::Ellipise(const Point & centre, int r_x, int r_y):
	centre(centre), r_x(r_x), r_y(r_y)
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

void Ellipise::draw4points(int cur_x, int cur_y) const
{
	pDrawPointFunc(centre.getX() - cur_x, centre.getY() - cur_y);
	pDrawPointFunc(centre.getX() - cur_x, centre.getY() + cur_y);
	pDrawPointFunc(centre.getX() + cur_x, centre.getY() - cur_y);
	pDrawPointFunc(centre.getX() + cur_x, centre.getY() + cur_y);
}
