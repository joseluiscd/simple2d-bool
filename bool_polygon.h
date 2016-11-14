#ifndef _BOOL_POLYGON_H
#define _BOOL_POLYGON_H

#include <list>
#include <vector>
#include <algorithm>

#include "polygon.h"
#include "segment.h"

class sortPoints {
public:
	const point2d* point;

	bool operator() (const point2d &i, const point2d &j) {
		return (squaredDistance(i, *point)<squaredDistance(j, *point));
	}

	sortPoints(const point2d *p): point(p) {};
};


std::vector<point2d>* intersectionPoints(const polygon2d &a, const polygon2d &b, int precision=3);
std::list<segment2d>* segmentsWithIntersectionPoints(const polygon2d &a, const polygon2d &b, int precision=3);
std::vector<segment2d>* polygonIntersection(const polygon2d &a, const polygon2d &b, int precision=3);
std::vector<segment2d>* polygonUnion(const polygon2d &a, const polygon2d &b, int precision=3);
std::vector<segment2d>* polygonDifference(const polygon2d &a, const polygon2d &b, int precision=3);

#endif
