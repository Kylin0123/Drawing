#include "MyPolygon.h"
#include "Line.h"

MyPolygon::MyPolygon(const std::vector<Point> & points):
	points(points)
{
}


MyPolygon::~MyPolygon()
{
}

void MyPolygon::draw() const
{
	/*TODO: please implement the algorithm of drawing polygons*/
	Point p1 = points[0];
	int i;
	for (i = 1; i < points.size(); i++) {
		Point p2 = points[i];
		Line line = Line(p1, p2);
		line.draw();
		p1 = p2;
	}
	Line(points[i - 1], points[0]).draw();
}
