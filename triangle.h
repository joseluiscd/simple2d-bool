#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "point.h"
#include "signo.h"

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
int puntoDentroDeTriangulo(const triangle2d& t, const point2d& p, int precision=3);

#endif
