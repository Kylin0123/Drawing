#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>
#include <list>
#include <memory>

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
	virtual void strongDraw() const override;
	virtual void translate(int x, int y);
	virtual void rotate(float angle);
	virtual void scale(float s1, float s2);
	void fill(int windowHeight);
	void unfill();
	std::vector<Point> & getPointVector() { return points; }
	MyPolygon cut(int xmin, int ymin, int xmax, int ymax);
protected:
	void addEdge(int index, int ymax, float x, float dx);
	void addAEdge(int index, const Edge & e);
private:
	std::vector<Point> points;
	std::vector<std::vector<Edge>> ET;
	std::vector<std::vector<Edge>> AET;
	std::vector<Point> fill_points;
};

