#include "MyPolygon.h"
#include "Line.h"
#include <algorithm>
#include <cassert>
#include <iostream>


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
	size_t i;
	for (i = 1; i < points.size(); i++) {
		Point p2 = points[i];
		Line line = Line(p1, p2);
		line.draw();
		p1 = p2;
	}
	Line(points[i - 1], points[0]).draw();
	for (Point p : fill_points) {
		p.draw();
	}
}

void MyPolygon::fill(int windowHeight)
{
	ET.clear();
	ET.resize(windowHeight);
	AET.clear();
	AET.resize(windowHeight);
	int n = points.size();
	for (int i = 0; i < n; i++) {
		const Point & curPoint = points[i];
		const Point & lPoint = points[(i - 1 + n) % n];
		const Point & rPoint = points[(i + 1) % n];

		int ymax1 = lPoint.getY();
		float x1 = curPoint.getX();
		float dx1 = (float)(lPoint.getX() - curPoint.getX()) / (lPoint.getY() - curPoint.getY());

		int ymax2 = rPoint.getY();
		float x2 = curPoint.getX();
		float dx2 = (float)(rPoint.getX() - curPoint.getX()) / (rPoint.getY() - curPoint.getY());

		bool lFlag = (lPoint.getY() - curPoint.getY()) > 0 ? true : false;
		bool rFlag = (rPoint.getY() - curPoint.getY()) > 0 ? true : false;

		if (lFlag && rFlag) {
			/*two neighbour points are both on the upper side*/
			addEdge(points[i].getY(), ymax1, x1, dx1);
			addEdge(points[i].getY(), ymax2, x2, dx2);
		}
		else if(lFlag ^ rFlag){
			/*two neighbour points are on different sides*/
			if (lFlag) addEdge(points[i].getY(), ymax1, x1, dx1);
			else if(rFlag) addEdge(points[i].getY(), ymax2, x2, dx2);
		}
		else {
			/*two neighbour points are both on the lower side*/

		}
	}

	for (int i = 0; i < windowHeight; i++) {
		if (i != 0) {
			for (auto it = AET[i - 1].begin(); it != AET[i - 1].end(); it++) {
				if (i >= it->ymax) continue;
				AET[i].push_back(Edge(it->ymax, it->x + it->dx, it->dx));
			}
		}

		/*check new lines*/
		if (!ET[i].empty())
			for (auto it = ET[i].begin(); it != ET[i].end(); it++)
				AET[i].push_back(*it);

		/*make sure all edges are sorted*/
		AET[i].sort([](const Edge & e1, const Edge & e2) -> bool {
			return e1.x < e2.x;
		});
	}
	
	for (int i = 0; i < windowHeight; i++) {
		for (auto it = AET[i].begin(); it != AET[i].end(); it++, it++) {
			for (int j = it->x; j < std::next(it)->x; j++) {
				fill_points.push_back(Point(j, i));
			}
		}
	}

}

void MyPolygon::addEdge(int index, int ymax, float x, float dx)
{
	std::list<Edge> & list = ET[index];
	list.push_back(Edge(ymax, x, dx));
}

void MyPolygon::addAEdge(int index, const Edge & e)
{
	std::list<Edge> & list = AET[index];
	list.push_back(e);
}
