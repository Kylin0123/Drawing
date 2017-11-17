#pragma once
#include <Windows.h>
#include <GL/glut.h>

class Shape
{
public:
	typedef void(WINAPI *PDrawPointFunc)(GLint, GLint);
	static PDrawPointFunc pDrawPointFunc;
	virtual void draw() const = 0;
};
