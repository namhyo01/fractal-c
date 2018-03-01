#include <vector>
#include "GLSupport.hpp"
#include <math.h>
#define COS 0.5
#define SIN 0.866
using namespace graphics;
double x1, x2, y, y2;
typedef struct Line {
	Point2f start;
	Point2f end;
};

Color White = { 1.0f, 1.0f, 1.0f };
Color Blue = { 0.0f, 0.0f, 1.0f };

int frameWidth = 512;
int frameHeight = 512;

void fractal(double x1, double y, double x2, double y2, int n)
{
	double dx, dy, xx1, xx2, xm, yy1, yy2, ym;
	if (n > 0)
	{
		dx = (x2 - x1) / 3;
		dy = (y2 - y) / 3;
		xx1 = x1 + dx;
		yy1 = y + dy;
		xx2 = x1 + 2 * dx;
		yy2 = y + 2 * dy;
		xm = COS*dx - SIN*dy + xx1;
		ym = COS*dy + SIN*dx + yy1;
		fractal(x1, y, xx1, yy1, n - 1);
		fractal(xx1, yy1, xm, ym, n - 1);
		fractal(xm, ym, xx2, yy2, n - 1);
		fractal(xx2, yy2, x2, y2, n - 1);
	}
	else
	{
		Point2f sp((float)x1, (float)y);
		Point2f ep((float)x2, (float)y2);
		drawLine(sp, ep, White);
	}
}
void render() {
	clear();

	/********************* draw part **************************/
	fractal(100, 100, 400, 100, 4);
	/**********************************************************/

}

void main(int argc, char* argv[]) {
	InitAndCreateWindow(argc, argv, "test", 512, 512, render);
}