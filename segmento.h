#include "punto.h"
#include "signo.h"

#include <stdexcept>

#ifndef _SEGMENTO_H
#define _SEGMENTO_H

#define segmento2Df segmento2D<float>
#define segmento2Dd segmento2D<double>

using namespace std;

enum SegmentoSegmento{
	iguales=0, cortan=1, coinciden=2, nada=3
};

/**
* Define el segmento A->B
*/
template<typename T>
struct segmento2D{
	punto2D<T> a;
	punto2D<T> b;
	segmento2D(T ax, T ay, T bx, T by): a(ax,ay), b(bx, by){};
	segmento2D(const punto2D<T>& aa, const punto2D<T>& bb): a(aa.x, aa.y), b(bb.x, bb.y){};
	segmento2D(): a(), b(){};
	segmento2D(const segmento2D<T>& orig): a(orig.a), b(orig.b){};
};

class paralelas: public exception {
};

// O(1)
template<typename T>
T areaSignada(const segmento2D<T>& a, const punto2D<T>& c){
	return areaSignada(a.a, a.b, c);
}

// O(1)
template<typename T>
SegmentoSegmento segmentoRespectoSegmento(segmento2D<T> a, segmento2D<T> b, int precision=3){
	//Son iguales??
	int x11 = signo(a.a.x, b.a.x, precision);
	int x12 = signo(a.a.x, b.b.x, precision);
	int x21 = signo(a.b.x, b.a.x, precision);
	int x22 = signo(a.b.x, b.b.x, precision);

	int y11 = signo(a.a.y, b.a.y, precision);
	int y12 = signo(a.a.y, b.b.y, precision);
	int y21 = signo(a.b.y, b.a.y, precision);
	int y22 = signo(a.b.y, b.b.y, precision);

	if(!( (x11 && x12 && x21 && x22)||(y11 && y12 && y21 && y22) )){
		//Coincide alguna X y alguna Y. Coinciden por un extremo o son iguales
		return signo(areaSignada(a, b.a), precision) || signo(areaSignada(a, b.b), precision) ? coinciden : iguales;
	} else {
		//O se cortan o nada
		return signo(areaSignada(a, b.a))==-signo(areaSignada(a, b.b)) && signo(areaSignada(b, a.a))==-signo(areaSignada(b, a.b)) ? cortan : nada;
	}
}

template<typename T>
bool puntoEnSegmento(punto2D<T> p, segmento2D<T> s, int precision=3){
	return signo(areaSignada(s, p))==0;
}

template<typename T>
punto2D<T> puntoMedio(segmento2D<T> s){
	punto2D<T> toRet;
	toRet.x = (s.a.x + s.b.x)/2;
	toRet.y = (s.a.y + s.b.y)/2;
	return toRet;
}

//Devuelve el punto de corte entre los 2 segmentos
template<typename T>
punto2D<T> puntoCorte(segmento2D<T> a, segmento2D<T> b, int precision=3){
	double s, t;
	double denom = a.a.x * ( b.b.y - b.a.y) + a.b.x * (b.a.y-b.b.y) + b.a.x * (a.b.y - a.a.y) + b.b.x*(a.a.y-a.b.y);
	punto2D<T> toRet;

	if (denom==0){
		throw paralelas(); // Son paralelas
	}

	s = (a.a.x * ( b.b.y - b.a.y) + b.a.x*(a.a.y-b.b.y) + b.b.x*(b.a.y-a.a.y) )/denom;
	t = -(a.a.x*(b.a.y-a.b.y)+a.b.x*(a.a.y-b.a.y)+b.a.x*(a.b.y-a.a.y))/denom;

	toRet.x = a.a.x+s*(a.b.x-a.a.x);
	toRet.y = a.a.y+t*(a.b.y-a.a.y);

	if((0<=s)&&(s<=1)&&(0<=t)&&(t<=1)){
		throw int(200); // No se cortan
	}

	return toRet;
}
#endif
