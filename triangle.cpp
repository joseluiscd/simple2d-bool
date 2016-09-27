#include "triangle.h"

// O(1)
double areaSignada(const triangle2d& a){
	return areaSignada(a.a, a.b, a.c);
}

/**
* Devuelve un entero con signo indicando si el punto está dentro del triángulo (1 o -1)
* o no (0)
*/
int puntoDentroDeTriangulo(const triangle2d& t, const point2d& p, int precision){
	int a = signo(areaSignada(t.a, t.b, p), precision);
	int b = signo(areaSignada(t.b, t.c, p), precision);
	int c = signo(areaSignada(t.c, t.a, p), precision);

	// Si está en algún borde devuelve el signo de la suma
	// Si no lo está comprueba si el signo de todos es igual (si=signo de uno, no=0)
	if(a && b && c){
		if((a==b) && (b==c)){
			return a;
		}
		return 0;
	}
	return signo(a + b + c);

}
