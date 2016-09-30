#include "polygon.h"

polygon2d::~polygon2d(){}


polygon2d::polygon2d():
	vertices(), segmentos()
	{}


polygon2d::polygon2d(const polygon2d& other):
	vertices(other.vertices),
	segmentos(other.segmentos)
	{}


void polygon2d::construirSegmentos(){
	minX = vertices.front().x;
	minY = vertices.front().y;
	maxX = vertices.front().x;
	maxY = vertices.front().y;

	for(auto i=++vertices.begin();i!=vertices.end();i++){
		if(i->x < minX) minX = i->x;
		if(i->y < minY) minY = i->y;
		if(i->x > maxX) maxX = i->x;
		if(i->y > maxY) maxY = i->y;

		segmentos.push_back(segment2d(*prev(i), *i));
	}

	//Unimos con el principio (Nos aseguramos de que el polígono es cerrado)
	segmentos.push_back(segment2d(vertices.back(), vertices.front()));

}

inclusionResult polygon2d::puntoEnPoligono(point2d p, int precision) const {
	//Use the bottom-left corner of the bounding box
	point2d origin(minX, minY);

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

		default:
		throw invalidPolygon("Point in polygon returned unexpected result.");
	}

}
