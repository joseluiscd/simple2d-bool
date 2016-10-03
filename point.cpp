#include "point.h"

int point2d::precision = 6;

point2d changeCoordinateSystem(const point2d& point, const double& x1, const double& y1, const double& x2, const double& y2, int precision){
	point2d toRet;

	double x = (point.x-x1)/(x2-x1);
	double y = (point.y-y1)/(y2-y1);

	long p = pow(10, precision);
	double ip = pow(10, -precision);

	toRet.x = ((double)((int)(x*p+0.5)))*ip;
	toRet.y = ((double)((int)(y*p+0.5)))*ip;

	return toRet;
}


point2d middlePoint(const point2d& a, const point2d& b){
	point2d toRet;
	toRet.x = (a.x + b.x)/2;
	toRet.y = (a.y + b.y)/2;
	return toRet;
}

double squaredDistance(const point2d& a, const point2d& b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

double distance(const point2d& a, const point2d& b){
    return std::sqrt(squaredDistance(a, b));
}
