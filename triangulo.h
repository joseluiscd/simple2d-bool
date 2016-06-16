#include "punto.h"
#include "signo.h"

#include <iostream>

#ifndef _TRIANGULO_H
#define _TRIANGULO_H

#define triangulo2Df triangulo2D<float>
#define triangulo2Dd triangulo2D<double>

/**
* Define el triángulo A->B->C->A
*/
template<typename T>
struct triangulo2D{
	punto2D<T> a;
	punto2D<T> b;
	punto2D<T> c;
	triangulo2D(const punto2D<T>& aa, const punto2D<T>& bb, const punto2D<T>& cc): a(aa.x, aa.y), b(bb.x, bb.y), c(cc.x,cc.y){};
	triangulo2D(): a(), b(), c(){};
	triangulo2D(const triangulo2D<T>& orig): a(orig.a), b(orig.b), c(orig.c){};
};


// O(1)
template<typename T>
T areaSignada(const triangulo2D<T>& a){
	return areaSignada(a.a, a.b, a.c);
}


/**
* Devuelve un entero con signo indicando si el punto está dentro del triángulo (1 o -1)
* o no (0)
* O(1)
*/
template<typename T>
int puntoDentroDeTriangulo(const triangulo2D<T>& t, const punto2D<T>& p, int precision=3){
	int a = signo(areaSignada(t.a, t.b, p), precision);
	int b = signo(areaSignada(t.b, t.c, p), precision);
	int c = signo(areaSignada(t.c, t.a, p), precision);

	// Si está en algún borde devuelve el signo de la suma
	// Si no lo está comprueba si el signo de todos es igual (si=signo de uno, no=0)

	return	a && b && c ? (a==b)&&(b==c) ?
			a : //Se cumplen los 2 casos
			0 : //Sólo se cumple el primero
			signo(a + b + c); //No se cumple ninguno

}

#endif
