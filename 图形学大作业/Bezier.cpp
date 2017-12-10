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
	for (const Point & p : points) {
		p.draw();
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
	for (const Point & p : points) {
		if (p.nearBy(x, y)) {
			focus_point = const_cast<Point*>(&p);
			return true;
		}
	}
	return false;
}
