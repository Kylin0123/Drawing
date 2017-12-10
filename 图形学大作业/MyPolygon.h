#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>
#include <list>
#include <memory>
#include "Rect.h"
#include "Cutable.h"

class Edge {
public:
	Edge(int ymax, float x, float dx) :
		ymax(ymax), x(x), dx(dx) {}
	int ymax;
	float x;
	float dx;
};

class MyPolygon :
	public Shape, public Cutable
{
public:
	MyPolygon(const std::vector<Point> & points);
	~MyPolygon();
	virtual void draw() const override;
	virtual void strongDraw() const override;
	virtual void moveFocusPointTo(int x, int y) override;
	virtual void translate(int x, int y) override;
	virtual void rotate(float angle) override;
	virtual void scale(float s1, float s2) override;

	virtual bool cut(int xmin, int ymin, int xmax, int ymax) override;

	bool nearBy(int x, int y);
	void fill();
	void unfill();
	void refill();
	
protected:
	void addEdge(int index, int ymax, float x, float dx);
	void addAEdge(int index, const Edge & e);
private:
	std::vector<Point> points;
	std::vector<std::vector<Edge>> ET;
	std::vector<std::vector<Edge>> AET;
	std::vector<Point> fill_points;
	Point* focus_point;
	Rect editRect;
};

