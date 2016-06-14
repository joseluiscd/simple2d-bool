#include <cmath>
#include "signo.h"
#include <iostream>

#ifndef _PUNTO_H
#define _PUNTO_H

#define punto2Df punto2D<float>
#define punto2Dd punto2D<double>

using namespace std;

template<typename T>
struct punto2D{
	T x;
	T y;
	punto2D(const T& ax, const T& ay): x(ax), y(ay){};
	punto2D(): x(0), y(0){};
};



/**
* Cambia el sistema de coordenadas.
*/
template<typename T>
punto2D<T> cambiaCoordenadas(const punto2D<T>& punto, const T& x1, const T& y1, const T& x2, const T& y2, int precision=3){
	punto2D<T> toRet;

	T x = (punto.x-x1)/(x2-x1);
	T y = (punto.y-y1)/(y2-y1);

	long p = pow(10, precision);
	T ip = pow(10, -precision);

	toRet.x = ((T)((int)(x*p+0.5)))*ip;
	toRet.y = ((T)((int)(y*p+0.5)))*ip;

	return toRet;
}

template<typename T>
punto2D<T> puntoMedio(punto2D<T> a, punto2D<T> b){
	punto2D<T> toRet;
	toRet.x = (a.x + b.x)/2;
	toRet.y = (a.y + b.y)/2;
	return toRet;
}

// O(1)
template<typename T>
T areaSignada(const punto2D<T>& a, const punto2D<T>& b, const punto2D<T>& c){
	return (a.x*b.y)+(a.y*c.x)+(b.x*c.y)-(c.x*b.y)-(b.x*a.y)-(a.x*c.y);
}

template<typename T>
T distanciaCuadrado(const punto2D<T>& a, const punto2D<T>& b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
#endif
