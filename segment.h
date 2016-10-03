#ifndef _SEGMENT_H
#define _SEGMENT_H

#include <stdexcept>
#include <cmath>

#include "math.h"
#include "point.h"


enum segmentRelSegment{
	EQUALS=0, INTERSECT=1, CONNECTED=2, NO_RELATION=3
};


class segment2d {
public:
	point2d a;
	point2d b;
	segment2d(double startx, double starty, double endx, double endy): a(startx, starty), b(endx, endy){};
	segment2d(const point2d& start, const point2d& end): a(start.x, start.y), b(end.x, end.y){};
	segment2d(): a(), b(){};
	segment2d(const segment2d& orig): a(orig.a), b(orig.b){};
};

class parallelSegments: public std::exception {
};


double doubleSignedArea(const segment2d& segment, const point2d& point);
bool pointInSegment(const point2d& point, const segment2d& segment);
segmentRelSegment segmentRelativeToSegment(const segment2d& a, const segment2d& b, int precision=6);
point2d middlePoint(const segment2d& s);
double cosAngle(const segment2d& a, const segment2d& b);
int orientation(const segment2d& a, const segment2d& b, int precision=3);
point2d intersectionPoint(const segment2d& a, const segment2d& b, int precision=3);
segment2d inverseSegment(const segment2d& s);

#endif
