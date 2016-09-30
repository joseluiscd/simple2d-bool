#ifndef _POINT_H
#define _POINT_H

#include "math.h"

class point2d {
public:
	double x;
	double y;

	static int precision;

    point2d(const double& ax, const double& ay): x(ax), y(ay){};
	point2d(): x(0), y(0){};

	bool operator==(const point2d& other) const{
		return !sign(this->x, other.x, precision) && !sign(this->y, other.y, precision);
	}

};

/**
* Change coordinate system
*/
point2d changeCoordinateSystem(const point2d& point, const double& x1,
		const double& y1, const double& x2, const double& y2, int precision=3);

point2d middlePoint(const point2d& a, const point2d& b);
double middleSignedArea(const point2d& a, const point2d& b, const point2d& c);
double squaredDistance(const point2d& a, const point2d& b);
double distance(const point2d &a, const point2d &b);

#endif
