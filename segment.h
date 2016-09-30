#ifndef _SEGMENT_H
#define _SEGMENT_H

#include <stdexcept>
#include <cmath>

#include "math.h"
#include "point.h"


enum SegmentoSegmento{
	iguales=0, cortan=1, coinciden=2, nada=3
};

/**
* Define el segmento A->B
*/
class segment2d {
public:
	point2d a;
	point2d b;
	segment2d(double startx, double starty, double endx, double endy): a(startx, starty), b(endx, endy){};
	segment2d(const point2d& start, const point2d& end): a(start.x, start.y), b(end.x, end.y){};
	segment2d(): a(), b(){};
	segment2d(const segment2d& orig): a(orig.a), b(orig.b){};
};

class paralelas: public std::exception {
};

class nocortan: public std::exception {
};

double areaSignada(const segment2d& segment, const point2d& point);
bool puntoEnSegmento(const point2d& point, const segment2d& segment);
SegmentoSegmento segmentoRespectoSegmento(const segment2d& a, const segment2d& b, int precision=6);
point2d puntoMedio(const segment2d& s);
double cosenoAngulo(const segment2d& a, const segment2d& b);
int orientacion(const segment2d& a, const segment2d& b, int precision=3);
point2d puntoCorte(const segment2d& a, const segment2d& b, int precision=3);
segment2d reves(const segment2d& s);

#endif
