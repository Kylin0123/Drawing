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

bool isLegal(float val) {
	return val >= -1 && val <= 1;
}

bool Line::getCrossPoint(const Line & line, Point & ret)
{
	int x1 = start.getX();
	int y1 = start.getY();
	int x2 = end.getX();
	int y2 = end.getY();

	int x3 = line.getStart().getX();
	int y3 = line.getStart().getY();
	int x4 = line.getEnd().getX();
	int y4 = line.getEnd().getY();

	if ((x2 - x1)*(y3 - y4) - (y2 - y1)*(x3 - x4) == 0)
		return false;

	float u1 = (float)((x3 - x1)*(y3 - y4) - (y3 - y1)*(x3 - x4)) / ((x2 - x1)*(y3 - y4) - (y2 - y1)*(x3 - x4));
	float u2 = (float)((x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1)) / ((x2 - x1)*(y3 - y4) - (y2 - y1)*(x3 - x4));

	std::cout << u1 << "," << u2 << std::endl;

	if (isLegal(u1) && isLegal(u2)) {
		ret = Point(x1 + u1*(x2 - x1), y1 + u1*(y2 - y1));
		return true;
	}

	return false;
}
