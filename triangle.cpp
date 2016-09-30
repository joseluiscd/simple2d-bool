#include "triangle.h"

// O(1)
double areaSignada(const triangle2d& a){
	return areaSignada(a.a, a.b, a.c);
}

/**
* Devuelve un entero con signo indicando si el punto está dentro del triángulo (1 o -1)
* o no (0)
*/
inclusionResult puntoEnTriangulo(const point2d& p, const triangle2d& t, int precision){
	int a = signo(areaSignada(t.a, t.b, p), precision);
	int b = signo(areaSignada(t.b, t.c, p), precision);
	int c = signo(areaSignada(t.c, t.a, p), precision);

	printf("%d, %d, %d\n", a, b, c);

	if(a && b && c){
		//None of the signed areas is 0, it's either inside or outside (no border)
		if((a==b) && (b==c)){
			//All 1 or -1, it's inside
			switch(a){
				case 1:	return INSIDE_POSITIVE;
				case -1: return INSIDE_NEGATIVE;
			}
		}
		//It's outside
		return OUTSIDE;
	}
	//It's on the border or outside
	if((!a && puntoEnSegmento(p, segment2d(t.a, t.b))) ||
	   (!b && puntoEnSegmento(p, segment2d(t.b, t.c))) ||
       (!c && puntoEnSegmento(p, segment2d(t.c, t.a)))){
			return BORDER;
	}
	printf("NOOP\n");
	//Not on a segment...
	return OUTSIDE;

}
