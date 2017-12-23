#include "Bezier.h"



Bezier::Bezier(const std::vector<Point> & points):
	points(points),
	editRect(0,0,0,0)
{
	editRect.reshape(points);
}


Bezier::~Bezier()
{
}

void Bezier::draw() const
{
	/*TODO: please implement the algorithm of drawing bezier lines*/
	if (points.size() == 3) {
		Point p1(points[0]);
		Point p2(points[1]);
		Point p3(points[2]);
		float dataX[3][1] = { {(float)p1.getX()}, {p2.getX()}, {p3.getX()} };
		Matrix<float> mX((float*)dataX, 3, 1);
		float dataY[3][1] = { { p1.getY() },{ p2.getY() },{ p3.getY() } };
		Matrix<float> mY((float*)dataY, 3, 1);
		float data2[3][3] = { {1, -2, 1}, {-2, 2, 0}, {1, 0, 0} };
		Matrix<float> m2((float*)data2, 3, 3);
		for (float u = 0.0f; u <= 1.0f; u += 0.001f) {
			float datau[1][3] = { u*u, u, 1 };
			Matrix<float> mu((float*)datau, 1, 3);
			Matrix<float> resultX = mu * m2 * mX;
			Matrix<float> resultY = mu * m2 * mY;
			float x = resultX.get(0, 0);
			float y = resultY.get(0, 0);
			Point(x, y).draw();
		}
	}
	else if (points.size() == 4) {
		Point p1(points[0]);
		Point p2(points[1]);
		Point p3(points[2]);
		Point p4(points[3]);
		float dataX[4][1] = { { p1.getX() },{ p2.getX() },{ p3.getX() }, {p4.getX()} };
		Matrix<float> mX((float*)dataX, 4, 1);
		float dataY[4][1] = { { p1.getY() },{ p2.getY() },{ p3.getY() },{ p4.getY() } };
		Matrix<float> mY((float*)dataY, 4, 1);
		float data2[4][4] = { { -1, 3, -3, 1 },{ 3, -6, 3, 0 },{ -3, 3, 0, 0 }, { 1, 0, 0, 0} };
		Matrix<float> m2((float*)data2, 4, 4);
		for (float u = 0.0f; u <= 1.0f; u += 0.001f) {
			float datau[1][4] = { u*u*u, u*u, u, 1 };
			Matrix<float> mu((float*)datau, 1, 4);
			Matrix<float> resultX = mu * m2 * mX;
			Matrix<float> resultY = mu * m2 * mY;
			float x = resultX.get(0, 0);
			float y = resultY.get(0, 0);
			Point(x, y).draw();
		}
	}
	else {
		assert(0); //please implement me
	}
}

void Bezier::strongDraw() const
{
	draw();
	for (const Point & p : points) {
		p.strongDraw();
	}
	editRect.draw();
}

void Bezier::moveFocusPointTo(int x, int y)
{
	focus_point->set(x, y);
	editRect.reshape(points);
}

void Bezier::translate(int x, int y)
{
	for (Point & p : points) {
		p.translate(x, y);
	}
	editRect.reshape(points);
}

void Bezier::rotate(float angle)
{
	for (Point & p : points) {
		p.translate(-editRect.getMidX(), -editRect.getMidY());
		p.rotate(angle);
		p.translate(editRect.getMidX(), editRect.getMidY());
	}
	editRect.reshape(points);
}

void Bezier::scale(float s1, float s2)
{
	for (Point & p : points) {
		p.translate(-editRect.getMidX(), -editRect.getMidY());
		p.scale(s1, s2);
		p.translate(editRect.getMidX(), editRect.getMidY());
	}
	editRect.reshape(points);
}

bool Bezier::nearBy(int x, int y)
{
	for (Point & p : points) {
		if (p.nearBy(x, y)) {
			focus_point = &p;
			return true;
		}
	}
	return false;
}
