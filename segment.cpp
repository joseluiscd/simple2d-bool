#include "segment.h"

double areaSignada(const segment2d& segment, const point2d& point){
	return middleSignedArea(segment.a, segment.b, point);
}

bool puntoEnSegmento(const point2d& point, const segment2d& segment){
	double v1x, v1y;
	double v2x, v2y;

    if(sign(areaSignada(segment, point))==0){
		v1x = point.x - segment.a.x;
		v1y = point.y - segment.a.y;
		v2x = point.x - segment.b.x;
		v2y = point.y - segment.b.y;

		//If sign == 0 -> the point is one of the segment's end points
		//If sign == -1 -> the point is inside the segment
        return sign(dotProduct(v1x, v1y, v2x, v2y)) <= 0;
    }
	return false;
}

//TODO: Change this (a.a.x, a.b.y...)
SegmentoSegmento segmentoRespectoSegmento(const segment2d& a, const segment2d& b, int precision){
	//Son iguales??
	int x11 = sign(a.a.x, b.a.x, precision);
	int x12 = sign(a.a.x, b.b.x, precision);
	int x21 = sign(a.b.x, b.a.x, precision);
	int x22 = sign(a.b.x, b.b.x, precision);

	int y11 = sign(a.a.y, b.a.y, precision);
	int y12 = sign(a.a.y, b.b.y, precision);
	int y21 = sign(a.b.y, b.a.y, precision);
	int y22 = sign(a.b.y, b.b.y, precision);

	if( !(x11 && x12 && x21 && x22) && !(y11 && y12 && y21 && y22) ){
		//Coincide alguna X y alguna Y. Coinciden por un extremo o son iguales
		return sign(areaSignada(a, b.a), precision) || sign(areaSignada(a, b.b), precision) ? coinciden : iguales;
	} else if(sign(areaSignada(a, b.a))==-sign(areaSignada(a, b.b)) && sign(areaSignada(b, a.a))==-sign(areaSignada(b, a.b))){
		return cortan;
	} else if(puntoEnSegmento(a.a, b) || puntoEnSegmento(a.b, b) || puntoEnSegmento(b.a, a) || puntoEnSegmento(b.b, a)){
		//Comprobamos si hay una intersección en forma de T
		return cortan;
	} else {
		return nada;
	}
}


point2d puntoMedio(const segment2d& s){
	return middlePoint(s.a, s.b);
}



double cosenoAngulo(const segment2d& a, const segment2d& b){
	return ((a.b.x-a.a.x) * (b.b.x-b.a.x) + (a.b.y-a.a.y) * (b.b.y-b.a.y))/(distance(a.a, a.b)*distance(b.a, b.b));
}


int orientacion(const segment2d& a, const segment2d& b, int precision){
	return sign(determinant(a.b.x-a.a.x, a.b.y-a.a.y, b.b.x-b.a.x, b.b.y-b.a.y), precision);
}

//Devuelve el punto de corte entre los 2 segmentos
point2d puntoCorte(const segment2d& a, const segment2d& b, int precision){
	point2d toRet;

	double a1 = a.b.y - a.a.y;
	double a2 = - a.b.x + a.a.x;
	double a3 = b.b.y - b.a.y;
	double a4 = - b.b.x + b.a.x;

	double denom = determinant(a1,a2,a3,a4);

	if (sign(denom, precision)==0){
		throw paralelas(); // Son paralelas
	}

	//Calcular la X
	a1 = a.a.x*(a.b.y-a.a.y) - a.a.y*(a.b.x-a.a.x);
	a3 = b.a.x*(b.b.y-b.a.y) - b.a.y*(b.b.x-b.a.x);

	toRet.x = determinant(a1,a2,a3,a4) / denom;

	//Calculamos la Y
	a1 = a.b.y - a.a.y;
	a2 = a.a.x*(a.b.y-a.a.y) - a.a.y*(a.b.x-a.a.x);
	a3 = b.b.y - b.a.y;
	a4 = b.a.x*(b.b.y-b.a.y) - b.a.y*(b.b.x-b.a.x);

	toRet.y = determinant(a1,a2,a3,a4) / denom;

	return toRet;
}


segment2d reves(const segment2d& s){
	return segment2d(s.b, s.a);
}
