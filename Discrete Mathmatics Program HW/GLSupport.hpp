#pragma once

#include <GL\glew.h>
#include <GL\glut.h>
#include <vector>

namespace graphics{

	class Point2f {
	public:
		float x;
		float y;

	public:
		Point2f() {};
		Point2f(float x, float y) :x(x), y(y) { };
	};

	typedef struct _Color3f {
		float r;
		float g;
		float b;
	}Color3f;

	typedef Color3f Color;
	
	void idle();

	void displayFunc();

	void InitAndCreateWindow(int argc, char* argv [], char* windowName, int width, int height, void(*idlefunc)(void));

	void plot(int x, int y, float r, float g, float b);

	void clear();

	void drawLine(Point2f sp, Point2f ep, Color c);
}
