#ifndef _BOOL_POLYGON_H
#define _BOOL_POLYGON_H

#include <list>
#include <vector>
#include <algorithm>

#include "polygon.h"
#include "segment.h"

class sortPuntos {
public:
	const point2d* punto;

	bool operator() (const point2d &i, const point2d &j) {
		return (squaredDistance(i, *punto)<squaredDistance(j, *punto));
	}

	sortPuntos(const point2d *p): punto(p) {};
};


std::vector<point2d>* intersectionPoints(const polygon2d &a, const polygon2d &b, int precision=3);
std::list<segment2d>* segmentosConPuntosDeCorte(const polygon2d &a, const polygon2d &b, int precision=3);
std::vector<segment2d>* interseccionPoligonos(const polygon2d &a, const polygon2d &b, int precision=3);
std::vector<segment2d>* unionPoligonos(const polygon2d &a, const polygon2d &b, int precision=3);
std::vector<segment2d>* diferenciaPoligonos(const polygon2d &a, const polygon2d &b, int precision=3);

#endif
