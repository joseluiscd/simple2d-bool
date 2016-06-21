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

class nocortan: public exception {
};

// O(1)
template<typename T>
T areaSignada(const segmento2D<T>& a, const punto2D<T>& c){
	return areaSignada(a.a, a.b, c);
}

// O(1)
template<typename T>
SegmentoSegmento segmentoRespectoSegmento(const segmento2D<T>& a, const segmento2D<T>& b, int precision=3){
	//Son iguales??
	int x11 = signo(a.a.x, b.a.x, precision);
	int x12 = signo(a.a.x, b.b.x, precision);
	int x21 = signo(a.b.x, b.a.x, precision);
	int x22 = signo(a.b.x, b.b.x, precision);

	int y11 = signo(a.a.y, b.a.y, precision);
	int y12 = signo(a.a.y, b.b.y, precision);
	int y21 = signo(a.b.y, b.a.y, precision);
	int y22 = signo(a.b.y, b.b.y, precision);

	if( !(x11 && x12 && x21 && x22) && !(y11 && y12 && y21 && y22) ){
		//Coincide alguna X y alguna Y. Coinciden por un extremo o son iguales
		return signo(areaSignada(a, b.a), precision) || signo(areaSignada(a, b.b), precision) ? coinciden : iguales;
	} else if(signo(areaSignada(a, b.a))==-signo(areaSignada(a, b.b)) && signo(areaSignada(b, a.a))==-signo(areaSignada(b, a.b))){
		return cortan;
	} else if(puntoEnSegmento(a.a, b, precision) || puntoEnSegmento(a.b, b, precision) || puntoEnSegmento(b.a, a, precision) || puntoEnSegmento(b.b, a, precision)){
		//Comprobamos si hay una intersección en forma de T
		return cortan;
	} else {
		return nada;
	}
}

template<typename T>
bool puntoEnSegmento(const punto2D<T>& p, const segmento2D<T>& s, int precision=3){
	if (signo(areaSignada(s, p))==0){
		//Están alineados
		T i = distanciaCuadrado(s.a, s.b); //Longitud al cuadrado del segmento
		if(distanciaCuadrado(s.a, p) > i || distanciaCuadrado(s.b, p) > i){
			return false;
		}
		return true;
	}
}

template<typename T>
punto2D<T> puntoMedio(const segmento2D<T>& s){
	return puntoMedio(s.a, s.b);
}

template<typename T>
inline T det(T a, T b, T c, T d){
	return (a*d - b*c);
}

template<typename T>
T cosenoAngulo(const segmento2D<T>& a, const segmento2D<T>& b){
	return ((a.b.x-a.a.x) * (b.b.x-b.a.x) + (a.b.y-a.a.y) * (b.b.y-b.a.y))/(sqrt(distanciaCuadrado(a.a, a.b))*sqrt(distanciaCuadrado(b.a, b.b)));
}

template<typename T>
int orientacion(const segmento2D<T>& a, const segmento2D<T>& b, int precision=3){
	return signo(det(a.b.x-a.a.x, a.b.y-a.a.y, b.b.x-b.a.x, b.b.y-b.a.y), precision);
}

//Devuelve el punto de corte entre los 2 segmentos
template<typename T>
punto2D<T> puntoCorte(const segmento2D<T>& a, const segmento2D<T>& b, int precision=3){
	punto2D<T> toRet;

	T a1 = a.b.y - a.a.y;
	T a2 = - a.b.x + a.a.x;
	T a3 = b.b.y - b.a.y;
	T a4 = - b.b.x + b.a.x;

	T denom = det(a1,a2,a3,a4);

	if (signo(denom, precision)==0){
		throw paralelas(); // Son paralelas
	}

	//Calcular la X
	a1 = a.a.x*(a.b.y-a.a.y) - a.a.y*(a.b.x-a.a.x);
	a3 = b.a.x*(b.b.y-b.a.y) - b.a.y*(b.b.x-b.a.x);

	toRet.x = det(a1,a2,a3,a4) / denom;

	//Calculamos la Y
	a1 = a.b.y - a.a.y;
	a2 = a.a.x*(a.b.y-a.a.y) - a.a.y*(a.b.x-a.a.x);
	a3 = b.b.y - b.a.y;
	a4 = b.a.x*(b.b.y-b.a.y) - b.a.y*(b.b.x-b.a.x);

	toRet.y = det(a1,a2,a3,a4) / denom;

	return toRet;
}

template<typename T>
segmento2D<T> reves(const segmento2D<T>& s){
	return segmento2D<T>(s.b, s.a);
}
#endif
