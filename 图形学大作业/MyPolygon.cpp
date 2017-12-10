#include "MyPolygon.h"
#include "Line.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <functional>
#include <climits>


MyPolygon::MyPolygon(const std::vector<Point> & points):
	points(points),
	editRect(0,0,0,0)
{
	editRect.reshape(points);
}


MyPolygon::~MyPolygon()
{
}

void MyPolygon::draw() const
{
	/*implement the algorithm of drawing polygons*/
	assert(points.size() >= 3);
	Point p1 = points[0];
	size_t i;
	for (i = 1; i < points.size(); i++) {
		Point p2 = points[i];
		Line line = Line(p1, p2);
		line.draw();
		p1 = p2;
	}
	Line(points[i - 1], points[0]).draw();
	for (const auto & p : fill_points) {
		p.draw();
	}
}

void MyPolygon::strongDraw() const
{
	draw();
	editRect.draw();
	for (const Point & p : points) {
		p.strongDraw();
	}
}

void MyPolygon::moveFocusPointTo(int x, int y)
{
	focus_point->set(x, y);
	editRect.reshape(points);
	refill();
}

void MyPolygon::translate(int x, int y)
{
	for (Point & p : points) {
		p.translate(x, y);
	}
	editRect.reshape(points);
	refill();
}

void MyPolygon::rotate(float angle)
{
	for (Point & p : points) {
		p.translate(-editRect.getMidX(), -editRect.getMidY());
		p.rotate(angle);
		p.translate(editRect.getMidX(), editRect.getMidY());
	}
	editRect.reshape(points);
	refill();
}

void MyPolygon::scale(float s1, float s2)
{
	for (Point & p : points) {
		p.translate(-editRect.getMidX(), -editRect.getMidY());
		p.scale(s1, s2);
		p.translate(editRect.getMidX(), editRect.getMidY());
	}
	editRect.reshape(points);
	refill();
}

bool MyPolygon::nearBy(int x, int y)
{
	for (const Point & p : points) {
		if (p.nearBy(x, y)) {
			focus_point = const_cast<Point*>(&p);
			return true;
		}
	}
	return false;
}

void MyPolygon::fill()
{
	int windowHeight = INT_MIN;
	for (const Point & p : points) {
		windowHeight = max(windowHeight, p.getY());
	}
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
		std::sort(AET[i].begin(), AET[i].end(),[](const Edge & e1, const Edge & e2) -> bool {
			return e1.x < e2.x;
		});
	}

	for (int i = 0; i < windowHeight; i++) {
		for (size_t it = 0; it < AET[i].size(); it += 2) {
			for (int j = (AET[i][it]).x; j < (AET[i][it+1]).x; j++) {
				fill_points.push_back(Point(j, i));
			}
		}
	}
}

void MyPolygon::unfill()
{
	fill_points.erase(fill_points.begin(), fill_points.end());
}

void MyPolygon::refill()
{
	if (fill_points.size() > 0) {
		unfill();
		fill();
	}
}

bool MyPolygon::cut(int xmin, int ymin, int xmax, int ymax)
{
	/*store the result of one side's cutting*/
	std::vector<Point> ret;

	auto back = points.end() - 1;
	for (auto it = points.begin(); it != points.end(); back = it, it++) {
		if ((it->getX() - xmin)*(back->getX() - xmin) < 0) {
			int y = (float)(it->getY() - back->getY()) 
				/ (it->getX() - back->getX())
				*(xmin - back->getX()) + back->getY();
			if ((it->getX() - xmin) <= 0) {
				//in - out
				ret.push_back(Point(xmin, y));
			}
			else {
				//out - in
				ret.push_back(Point(xmin, y));
				ret.push_back(*it);
			}
		}
		else if (it->getX() - xmin >= 0 && back->getX() - xmin >= 0) {
			ret.push_back(*it);
		}
		else {
			//points in
		}
	}

	if (ret.size() < 3) return false;

	/*ready for the other side's cutting*/
	points = ret;
	ret.erase(ret.begin(), ret.end());
	back = points.end() - 1;
	for (auto it = points.begin(); it != points.end(); back = it, it++) {
		if ((it->getX() - xmax)*(back->getX() - xmax) < 0) {
			int y = (float)(it->getY() - back->getY()) 
				/ (it->getX() - back->getX())
				*(xmax - back->getX()) + back->getY();
			if ((it->getX() - xmax) <= 0) {
				//out - in
				ret.push_back(Point(xmax, y));
				ret.push_back(*it);
			}
			else {
				//in - out
				ret.push_back(Point(xmax, y));
			}
		}
		else if (it->getX() - xmax <= 0 && back->getX() - xmax <= 0) {
			ret.push_back(*it);
		}
		else {
			//points in
		}
	}

	if (ret.size() < 3) return false;

	points = ret;
	ret.erase(ret.begin(), ret.end());
	back = points.end() - 1;
	for (auto it = points.begin(); it != points.end(); back = it, it++) {
		if ((it->getY() - ymin)*(back->getY() - ymin) < 0) {
			int x = (float)(it->getX() - back->getX())
				/ (it->getY() - back->getY())
				*(ymin - back->getY()) + back->getX();
			if ((it->getY() - ymin) <= 0) {
				//in - out
				ret.push_back(Point(x, ymin));
			}
			else {
				//out - in
				ret.push_back(Point(x, ymin));
				ret.push_back(*it);
			}
		}
		else if (it->getY() - ymin >= 0 && back->getY() - ymin >= 0) {
			ret.push_back(*it);
		}
		else {
			//points in
		}
	}

	if (ret.size() < 3) return false;

	points = ret;
	ret.erase(ret.begin(), ret.end());
	back = points.end() - 1;
	for (auto it = points.begin(); it != points.end(); back = it, it++) {
		if ((it->getY() - ymax)*(back->getY() - ymax) < 0) {
			int x = (float)(it->getX() - back->getX())
				/ (it->getY() - back->getY())
				*(ymax - back->getY()) + back->getX();
			if ((it->getY() - ymax) <= 0) {
				//out - in
				ret.push_back(Point(x, ymax));
				ret.push_back(*it);
			}
			else {
				//in - out
				ret.push_back(Point(x, ymax));
			}
		}
		else if (it->getY() - ymax <= 0 && back->getY() - ymax <= 0) {
			ret.push_back(*it);
		}
		else {
			//points in
		}
	}

	if (ret.size() < 3) return false;

	points = ret;

	editRect.reshape(points);
	refill();

	return true;
}

void MyPolygon::addEdge(int index, int ymax, float x, float dx)
{
	std::vector<Edge> & list = ET[index];
	list.push_back(Edge(ymax, x, dx));
}

void MyPolygon::addAEdge(int index, const Edge & e)
{
	std::vector<Edge> & list = AET[index];
	list.push_back(e);
}
