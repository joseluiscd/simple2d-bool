#ifndef _POINT_H
#define _POINT_H

#include "signo.h"

class point2d {
public:
	double x;
	double y;

	static int precision;

    point2d(const double& ax, const double& ay): x(ax), y(ay){};
	point2d(): x(0), y(0){};

	bool operator==(const point2d& other) const{
		return !signo(this->x, other.x, precision) && !signo(this->y, other.y, precision);
	}

};

/**
* Change coordinate system
*/
point2d cambiaCoordenadas(const point2d& point, const double& x1,
		const double& y1, const double& x2, const double& y2, int precision=3);

point2d puntoMedio(const point2d& a, const point2d& b);
double areaSignada(const point2d& a, const point2d& b, const point2d& c);
double distanciaCuadrado(const point2d& a, const point2d& b);
double distancia(const point2d &a, const point2d &b);

#endif
