#include "polygon.h"

polygon2d::~polygon2d(){}


polygon2d::polygon2d():
	vertices(), segmentos()
	{}


polygon2d::polygon2d(const polygon2d& otro):
	vertices(otro.vertices),
	segmentos(otro.segmentos)
	{}


void polygon2d::construirSegmentos(){
	for(auto i=++vertices.begin();i!=vertices.end();i++){
		segmentos.push_back(segment2d(*prev(i), *i));
	}
	//Unimos con el principio (Nos aseguramos de que el polígono es cerrado)
	segmentos.push_back(segment2d(vertices.back(), vertices.front()));
}

void polygon2d::construirVertices(){
	for(auto it=segmentos.begin(); it!=segmentos.end(); ++it){
		vertices.push_back(it->a);
	}
}

bool polygon2d::puntoEnPoligono(point2d p, int precision) const {
	point2d origen(0,0);
	int suma = 0;
	for(auto i=segmentos.begin();i!=segmentos.end();i++){
		suma+= signo(puntoDentroDeTriangulo(triangle2d(i->a, i->b, origen),p, precision));
	}
	return suma!=0;
}
