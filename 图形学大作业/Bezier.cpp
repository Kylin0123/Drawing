#include "Bezier.h"



Bezier::Bezier(const std::vector<Point> & points):
	points(points)
{
}


Bezier::~Bezier()
{
}

void Bezier::draw() const
{
	/*TODO: please implement the algorithm of drawing bezier lines*/
	for (Point p : points) {
		p.draw();
	}
}
