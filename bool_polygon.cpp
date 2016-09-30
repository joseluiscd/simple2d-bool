#include "bool_polygon.h"

std::vector<point2d>* intersectionPoints(const polygon2d &a, const polygon2d &b, int precision){
	std::vector<point2d>* vert1 = new std::vector<point2d>();
	for(auto i = a.segments.begin(); i != a.segments.end(); i++){
		std::vector<point2d> cortes_segmento;
		for(auto j = b.segments.begin(); j!=b.segments.end(); j++){
			if(segmentoRespectoSegmento(*i, *j, precision)==cortan){
				//calculamos el punto de corte
				cortes_segmento.push_back(puntoCorte(*i, *j));
			}
		}

		vert1->push_back(i->a);
		if(cortes_segmento.size()>0){
			sort(cortes_segmento.begin(), cortes_segmento.end(), sortPuntos(&i->a));
			for(int j=0; j<cortes_segmento.size(); j++){
				vert1->push_back(cortes_segmento[j]);
			}
		}
	}
	return vert1;
}

std::list<segment2d>* segmentosConPuntosDeCorte(const polygon2d &a, const polygon2d &b, int precision){
	std::vector<point2d>* vert1 = intersectionPoints(a, b, precision);

	std::list<segment2d>* ret = new std::list<segment2d>();


	for(int i=1; i<vert1->size(); i++){
		ret->push_back(segment2d((*vert1)[i-1], (*vert1)[i]));
	}
	ret->push_back(segment2d(vert1->back(), vert1->front()));

	delete vert1;
	return ret;

}

std::vector<segment2d>* interseccionPoligonos(const polygon2d &a, const polygon2d &b, int precision){
	std::vector<segment2d>* ret = new std::vector<segment2d>();
	std::list<segment2d>* segmentos1 = segmentosConPuntosDeCorte(a, b, precision);
	std::list<segment2d>* segmentos2 = segmentosConPuntosDeCorte(b, a, precision);

	for(auto it=segmentos1->begin(); it!=segmentos1->end(); it++){
		point2d pmedio = puntoMedio(*it);
		if(b.pointInPolygon(pmedio)){
			ret->push_back(*it);
		}
	}

	for(auto it=segmentos2->begin(); it!=segmentos2->end(); it++){
		point2d pmedio = puntoMedio(*it);
		if(a.pointInPolygon(pmedio)){
			ret->push_back(*it);
		}
	}

	delete segmentos1;
	delete segmentos2;

	return ret;
}

std::vector<segment2d>* unionPoligonos(const polygon2d &a, const polygon2d &b, int precision){
	std::vector<segment2d>* ret = new std::vector<segment2d>();
	std::list<segment2d>* segmentos1 = segmentosConPuntosDeCorte(a, b, precision);
	std::list<segment2d>* segmentos2 = segmentosConPuntosDeCorte(b, a, precision);

	for(auto it=segmentos1->begin(); it!=segmentos1->end(); it++){
		point2d pmedio = puntoMedio(*it);
		if(!b.pointInPolygon(pmedio)){
			ret->push_back(*it);
		}
	}

	for(auto it=segmentos2->begin(); it!=segmentos2->end(); it++){
		point2d pmedio = puntoMedio(*it);
		if(!a.pointInPolygon(pmedio)){
			ret->push_back(*it);
		}
	}

	delete segmentos1;
	delete segmentos2;

	return ret;

}

std::vector<segment2d>* diferenciaPoligonos(const polygon2d &a, const polygon2d &b, int precision){
	std::vector<segment2d>* ret = new std::vector<segment2d>();
	std::list<segment2d>* segmentos1 = segmentosConPuntosDeCorte(a, b, precision);
	std::list<segment2d>* segmentos2 = segmentosConPuntosDeCorte(b, a, precision);

	for(auto it=segmentos1->begin(); it!=segmentos1->end(); it++){
		point2d pmedio = puntoMedio(*it);
		if(!b.pointInPolygon(pmedio)){
			ret->push_back(*it);
		}
	}

	for(auto it=segmentos2->begin(); it!=segmentos2->end(); it++){
		point2d pmedio = puntoMedio(*it);
		if(a.pointInPolygon(pmedio)){
			ret->push_back(reves(*it));
		}
	}

	delete segmentos1;
	delete segmentos2;

	return ret;

}
