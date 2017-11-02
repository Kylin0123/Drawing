#include "Line.h"
#include <cmath>


Line::Line(const Point & start, const Point & end):
	start(start), end(end)
{
}


Line::~Line()
{
}

void Line::setEnd(const Point & end)
{
	this->end = end;
}

void Line::draw() const
{
	/*TODO:please implement the algorithm of drawing lines*/
	int delta_x = end.getX() - start.getX();
	int delta_y = end.getY() - start.getY();
	int abs_delta_x = abs(delta_x);
	int abs_delta_y = abs(delta_y);
	int cur_x = start.getX();
	int cur_y = start.getY();
	int step_x = delta_x > 0 ? 1 : -1;
	int step_y = delta_y > 0 ? 1 : -1;

	pDrawPointFunc(cur_x, cur_y);

	if (abs_delta_x >= abs_delta_y) {
		int two_abs_delta_y = 2 * abs_delta_y;
		int two_abs_delta_y_minus_two_abs_delta_x = two_abs_delta_y - 2 * abs_delta_x;
		int p = two_abs_delta_y - abs_delta_x;

		for (int k = 0; k <= abs_delta_x; k++) {
			if (p < 0) {
				cur_x += step_x;
				pDrawPointFunc(cur_x, cur_y);
				p += two_abs_delta_y;
			}
			else if (p >= 0) {
				cur_x += step_x;
				cur_y += step_y;
				pDrawPointFunc(cur_x, cur_y);
				p += two_abs_delta_y_minus_two_abs_delta_x;
			}
		}
	}
	else if (abs_delta_x < abs_delta_y) {
		int two_abs_delta_x = 2 * abs_delta_x;
		int two_abs_delta_x_minus_two_abs_delta_y = two_abs_delta_x - 2 * abs_delta_y;
		int p = two_abs_delta_x - abs_delta_y;

		for (int k = 0; k <= abs_delta_y; k++) {
			if (p < 0) {
				cur_y += step_y;
				pDrawPointFunc(cur_x, cur_y);
				p += two_abs_delta_x;
			}
			else if (p >= 0) {
				cur_x += step_x;
				cur_y += step_y;
				pDrawPointFunc(cur_x, cur_y);
				p += two_abs_delta_x_minus_two_abs_delta_y;
			}
		}
	}
}
