#include "poligono.h"
#include "segmento.h"
#include <list>
#include <vector>
#include <algorithm>

#ifndef _BOOL_POLIGONO_H
#define _BOOL_POLIGONO_H

using namespace std;

template<typename T>
struct sortPuntos {
	const punto2D<T>* punto;
	bool operator() (const punto2D<T>& i, const punto2D<T>& j) {
		return (distanciaCuadrado(i, *punto)<distanciaCuadrado(j, *punto));
	}

	sortPuntos(const punto2D<T>* p): punto(p) {};
};


template<typename T>
vector<punto2D<T> >* puntosDeCorte(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	vector<punto2D<T> >* vert1 = new vector<punto2D<T> >();
	for(auto i = a.segmentos.begin(); i != a.segmentos.end(); i++){
		vector<punto2D<T> > cortes_segmento;
		for(auto j = b.segmentos.begin(); j!=b.segmentos.end(); j++){
			if(segmentoRespectoSegmento(*i, *j, precision)==cortan){
				//calculamos el punto de corte
				cortes_segmento.push_back(puntoCorte(*i, *j));
			}
		}

		vert1->push_back(i->a);
		if(cortes_segmento.size()>0){
			sort(cortes_segmento.begin(), cortes_segmento.end(), sortPuntos<T>(&i->a));
			for(int j=0; j<cortes_segmento.size(); j++){
				vert1->push_back(cortes_segmento[j]);
			}
		}
	}
	return vert1;
}

template<typename T>
list<segmento2D<T> >* segmentosConPuntosDeCorte(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	vector<punto2D<T> >* vert1 = puntosDeCorte(a, b, precision);

	list<segmento2D<T> >* ret = new list<segmento2D<T> >();


	for(int i=1; i<vert1->size(); i++){
		ret->push_back(segmento2D<T>((*vert1)[i-1], (*vert1)[i]));
	}
	ret->push_back(segmento2D<T>(vert1->back(), vert1->front()));

	delete vert1;
	return ret;

}

template<typename T>
vector<segmento2D<T> >* interseccionPoligonos(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	vector<segmento2D<T> >* ret = new vector<segmento2D<T> >();
	list<segmento2D<T> >* segmentos1 = segmentosConPuntosDeCorte(a, b, precision);
	list<segmento2D<T> >* segmentos2 = segmentosConPuntosDeCorte(b, a, precision);

	for(auto it=segmentos1->begin(); it!=segmentos1->end(); it++){
		punto2D<T> pmedio = puntoMedio(*it);
		if(b.puntoEnPoligono(pmedio)){
			ret->push_back(*it);
		}
	}

	for(auto it=segmentos2->begin(); it!=segmentos2->end(); it++){
		punto2D<T> pmedio = puntoMedio(*it);
		if(a.puntoEnPoligono(pmedio)){
			ret->push_back(*it);
		}
	}

	delete segmentos1;
	delete segmentos2;

	return ret;
}

template<typename T>
vector<segmento2D<T> >* unionPoligonos(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	vector<segmento2D<T> >* ret = new vector<segmento2D<T> >();
	list<segmento2D<T> >* segmentos1 = segmentosConPuntosDeCorte(a, b, precision);
	list<segmento2D<T> >* segmentos2 = segmentosConPuntosDeCorte(b, a, precision);

	for(auto it=segmentos1->begin(); it!=segmentos1->end(); it++){
		punto2D<T> pmedio = puntoMedio(*it);
		if(!b.puntoEnPoligono(pmedio)){
			ret->push_back(*it);
		}
	}

	for(auto it=segmentos2->begin(); it!=segmentos2->end(); it++){
		punto2D<T> pmedio = puntoMedio(*it);
		if(!a.puntoEnPoligono(pmedio)){
			ret->push_back(*it);
		}
	}

	delete segmentos1;
	delete segmentos2;

	return ret;

}

template<typename T>
vector<segmento2D<T> >* diferenciaPoligonos(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	vector<segmento2D<T> >* ret = new vector<segmento2D<T> >();
	list<segmento2D<T> >* segmentos1 = segmentosConPuntosDeCorte(a, b, precision);
	list<segmento2D<T> >* segmentos2 = segmentosConPuntosDeCorte(b, a, precision);

	for(auto it=segmentos1->begin(); it!=segmentos1->end(); it++){
		punto2D<T> pmedio = puntoMedio(*it);
		if(!b.puntoEnPoligono(pmedio)){
			ret->push_back(*it);
		}
	}

	for(auto it=segmentos2->begin(); it!=segmentos2->end(); it++){
		punto2D<T> pmedio = puntoMedio(*it);
		if(a.puntoEnPoligono(pmedio)){
			ret->push_back(reves(*it));
		}
	}

	delete segmentos1;
	delete segmentos2;

	return ret;

}

#endif
