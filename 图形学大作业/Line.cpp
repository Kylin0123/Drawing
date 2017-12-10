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
	/*implement the algorithm of drawing lines*/
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

void Line::strongDraw() const
{
	draw();
	start.strongDraw();
	end.strongDraw();
}

void Line::moveFocusPointTo(int x, int y)
{
	focus_point->set(x, y);
}

void Line::translate(int x, int y)
{
	start.translate(x, y);
	end.translate(x, y);
}

void Line::rotate(float angle)
{
	int midX = (start.getX() + end.getX()) / 2;
	int midY = (start.getY() + end.getY()) / 2;
	start.translate(-midX, -midY);
	start.rotate(angle);
	start.translate(midX, midY);
	end.translate(-midX, -midY);
	end.rotate(angle); 
	end.translate(midX, midY);
}

void Line::scale(float s1, float s2)
{
	int midX = (start.getX() + end.getX()) / 2;
	int midY = (start.getY() + end.getY()) / 2;
	start.translate(-midX, -midY);
	start.scale(s1, s2);
	start.translate(midX, midY);
	end.translate(-midX, -midY);
	end.scale(s1, s2);
	end.translate(midX, midY);
}

bool Line::cut(int xmin, int ymin, int xmax, int ymax)
{
	Point p1 = start;
	Point p2 = end;

	int p[5], q[5];
	float u1 = 0, u2 = 1;
	bool flag = false;
	p[1] = p1.getX() - p2.getX();
	p[2] = p2.getX() - p1.getX();
	p[3] = p1.getY() - p2.getY();
	p[4] = p2.getY() - p1.getY();

	q[1] = p1.getX() - xmin;
	q[2] = xmax - p1.getX();
	q[3] = p1.getY() - ymin;
	q[4] = ymax - p1.getY();

	for (int i = 1; i <= 4; i++) {
		float r = (float)q[i] / p[i];
		if (p[i] < 0) {
			u1 = max(u1, r);
			if (u1 > u2) {
				flag = true;
			}
		}
		else if (p[i] > 0) {
			u2 = min(u2, r);
			if (u1 > u2) {
				flag = true;
			}
		}
		else if (p[i] == 0 && q[i] < 0) {
			flag = true;
		}
	}

	if (flag) {
		return false;
	}

	start = Point(p1.getX() + (int)(u1 * (p2.getX() - p1.getX())),
		p1.getY() + (int)(u1 * (p2.getY() - p1.getY())));
	end = Point(p1.getX() + (int)(u2 * (p2.getX() - p1.getX())),
		p1.getY() + (int)(u2 * (p2.getY() - p1.getY())));
}

bool Line::nearBy(int x, int y)
{
	if (start.nearBy(x, y)) {
		focus_point = &start;
		return true;
	}
	else if (end.nearBy(x, y)) {
		focus_point = &end;
		return true;
	}
	return false;
}
