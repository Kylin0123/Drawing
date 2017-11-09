#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>
#include <list>

class Edge {
public:
	Edge(int ymax, float x, float dx) :
		ymax(ymax), x(x), dx(dx) {}
	int ymax;
	float x;
	float dx;
};

class MyPolygon :
	public Shape
{
public:
	MyPolygon(const std::vector<Point> & points);
	~MyPolygon();
	virtual void draw() const override;
	void fill(int windowHeight);
protected:
	void addEdge(int index, int ymax, float x, float dx);
	void addAEdge(int index, const Edge & e);
private:
	std::vector<Point> points;
	std::vector<std::list<Edge>> ET;
	std::vector<std::list<Edge>> AET;
	std::vector<Point> fill_points;
};

