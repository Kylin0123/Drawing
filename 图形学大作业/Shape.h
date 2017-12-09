#pragma once
#include <Windows.h>
#include <GL/glut.h>
#include <cassert>

class Shape
{
public:
	typedef void(WINAPI *PDrawPointFunc)(GLint, GLint);
	static PDrawPointFunc pDrawPointFunc;
	virtual void draw() const = 0;
	virtual void strongDraw() const { assert(0); }
	virtual void translate(int x, int y) { assert(0); };
	virtual void rotate(float angle) { assert(0); }
	virtual void scale(float s1, float s2) { assert(0); }
};
