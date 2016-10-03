#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "segment.h"
#include "point.h"
#include "math.h"

//TODO: Decidir si esto va aquí
enum inclusionResult {
	OUTSIDE = 0,
	BORDER = 1,
	INSIDE_POSITIVE = 2,
	INSIDE_NEGATIVE = -2
};


class triangle2d {
public:
	point2d a;
	point2d b;
	point2d c;

	triangle2d(const point2d& aa, const point2d& bb, const point2d& cc): a(aa.x, aa.y), b(bb.x, bb.y), c(cc.x,cc.y){};
	triangle2d(): a(), b(), c(){};
	triangle2d(const triangle2d& orig): a(orig.a), b(orig.b), c(orig.c){};
};

double doubleSignedArea(const point2d& a, const point2d& b, const point2d& c);
double doubleSignedArea(const segment2d& segment, const point2d& point);
double doubleSignedArea(const triangle2d& a);
inclusionResult pointInTriangle(const point2d& p, const triangle2d& t, int precision=3);
int orientation(const triangle2d& t);

#endif
