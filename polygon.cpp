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

inclusionResult polygon2d::puntoEnPoligono(point2d p, int precision) const {
	point2d origin(0,0);

	int sum = 0;

	for(auto current=segmentos.begin(); current!=segmentos.end(); current++){
		//Check if point is in a segment
		if(puntoEnSegmento(p, *current)){
			return BORDER;
		}

		//If it's not in a border, check if it's inside the triangle
		inclusionResult c = puntoEnTriangulo(p, triangle2d(current->a, current->b, origin), precision);
		switch(c){
			case BORDER: sum += 1; break; //We add +1/2
			case INSIDE_POSITIVE: sum += 2; break; //We add 1
			case INSIDE_NEGATIVE: sum -= 2; break; //Subtract 1
			default: break;
		}
	}

	switch(sum){
		case 0: return OUTSIDE;

		case 2: return INSIDE_POSITIVE;
		case -2: return INSIDE_NEGATIVE;

		default: throw invalidPolygon();
	}

}
