#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "segment.h"
#include "point.h"
#include "signo.h"

//TODO: Decidir si esto va aquí
enum inclusionResult {
	OUTSIDE = 0,
	BORDER = 1,
	INSIDE_POSITIVE = 2,
	INSIDE_NEGATIVE = -2
};

/**
* Define el triángulo A->B->C->A
*/
class triangle2d {
public:
	point2d a;
	point2d b;
	point2d c;

	triangle2d(const point2d& aa, const point2d& bb, const point2d& cc): a(aa.x, aa.y), b(bb.x, bb.y), c(cc.x,cc.y){};
	triangle2d(): a(), b(), c(){};
	triangle2d(const triangle2d& orig): a(orig.a), b(orig.b), c(orig.c){};
};

double areaSignada(const triangle2d& a);
inclusionResult puntoEnTriangulo(const point2d& p, const triangle2d& t, int precision=3);

#endif
