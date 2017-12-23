#pragma once
#include <Windows.h>
#include <GL/glut.h>
#include <cassert>
#include <memory>

class Shape
{
public:
	typedef void(WINAPI *PDrawPointFunc)(GLint, GLint);
	static PDrawPointFunc pDrawPointFunc;
	virtual void draw() const = 0;
	virtual void strongDraw() const = 0;
	virtual void moveFocusPointTo(int x, int y) = 0;
	virtual void translate(int x, int y) = 0;
	virtual void rotate(float angle) = 0;
	virtual void scale(float s1, float s2) = 0;
	virtual bool nearBy(int x, int y) = 0;
};
