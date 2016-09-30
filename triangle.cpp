#include "triangle.h"

//TODO: Traducir comentarios
// O(1)
double doubleSignedArea(const triangle2d& a){
	return doubleSignedArea(a.a, a.b, a.c);
}

int orientation(const triangle2d& triangle){
	return orientation(segment2d(triangle.a, triangle.b), segment2d(triangle.b, triangle.c));
}


/**
* Devuelve un entero con signo indicando si el punto está dentro del triángulo (1 o -1)
* o no (0)
*/
inclusionResult pointInTriangle(const point2d& p, const triangle2d& t, int precision){
	int a = sign(doubleSignedArea(t.a, t.b, p), precision);
	int b = sign(doubleSignedArea(t.b, t.c, p), precision);
	int c = sign(doubleSignedArea(t.c, t.a, p), precision);

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
	if((!a && pointInSegment(p, segment2d(t.a, t.b))) ||
	   (!b && pointInSegment(p, segment2d(t.b, t.c))) ||
       (!c && pointInSegment(p, segment2d(t.c, t.a)))){
			return BORDER;
	}

	//Not on a segment...
	return OUTSIDE;

}
