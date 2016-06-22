#include "punto.h"
#include "segmento.h"
#include "triangulo.h"

#include <list>
#include <stdexcept>
#include <iostream>
#include <map>
#include <fstream>


#ifndef _POLIGONO_H
#define _POLIGONO_H

#define poligono2Df poligono2D<float>
#define poligono2Dd poligono2D<double>

using namespace std;

class poligonoInvalido: public exception {
};

template<typename T>
class poligono2D{
	private:
	typedef punto2D<T> punto;
	typedef segmento2D<T> segmento;
	typedef poligono2D<T> poligono;

	typedef typename list<punto>::iterator punto_it;
	typedef typename list<punto>::const_iterator punto_it_c;
	typedef typename list<segmento>::iterator segmento_it;

	public:
	list<punto> vertices;
	list<segmento> segmentos;

	public:
	void construirSegmentos();
	bool puntoEnPoligono(punto p, int precision=3) const;

	poligono2D();
	poligono2D(const list<punto>& v);
	poligono2D(const poligono2D<T>& otro);
	virtual ~poligono2D();


};

template<typename T>
poligono2D<T>::~poligono2D(){}


template<typename T>
poligono2D<T>::poligono2D():
	vertices(), segmentos()
	{}

template<typename T>
poligono2D<T>::poligono2D(const list<punto>& v):
	segmentos()
	{
		if(v.size()==1){
			//Es un punto
			throw punto2D<T>(v.front());
		} else if(v.size()==2){
			//Es un segmento
			throw segmento2D<T>(*v.begin(), *v.rbegin());
		}

		for(punto_it_c i=v.begin();i!=v.end();i++){
			vertices.push_back(*i);
		}
		construirSegmentos();
	}

template<typename T>
poligono2D<T>::poligono2D(const poligono2D<T>& otro):
	vertices(otro.vertices),
	segmentos(otro.segmentos)
	{}
// O(n)
template<typename T>
void poligono2D<T>::construirSegmentos(){
	for(punto_it i=++vertices.begin();i!=vertices.end();i++){
		segmentos.push_back(segmento(*prev(i), *i));
	}
	//Unimos con el principio (Nos aseguramos de que el polígono es cerrado)
	segmentos.push_back(segmento(vertices.back(), vertices.front()));
}

// O(n)
template<typename T>
bool poligono2D<T>::puntoEnPoligono(punto p, int precision) const {
	punto origen(0,0);
	int suma = 0;
	for(auto i=segmentos.begin();i!=segmentos.end();i++){
		suma+= signo(puntoDentroDeTriangulo(triangulo2D<T>(i->a, i->b, origen),p, precision));
	}
	return suma!=0;
}


#endif
