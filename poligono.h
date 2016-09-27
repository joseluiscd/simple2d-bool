#include "point.h"
#include "segment.h"
#include "triangle.h"

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

	public:
	list<punto> vertices;
	list<segmento> segmentos;

	public:
	void construirSegmentos();
	void construirVertices();
	bool puntoEnPoligono(punto p, int precision=3) const;

	poligono2D();

	template< template<typename, typename> typename container, typename A >
	poligono2D(const container<punto2D<T>, A>& v);

	template< template<typename, typename> typename container, typename A >
	poligono2D(const container<segmento2D<T>, A>& v);

	template< template<typename> typename iterator_t >
	poligono2D(const iterator_t<punto2D<T> >& inicio, const iterator_t<punto2D<T> >& fin);

	template< template<typename> typename iterator_t >
	poligono2D(const iterator_t<segmento2D<T> >& inicio, const iterator_t<segmento2D<T> >& fin);

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
template<template<typename, typename> typename container, typename A >
poligono2D<T>::poligono2D(const container<punto2D<T>, A>& v):
	poligono2D(v.begin(), v.end())
{
}

template<typename T>
template<template<typename, typename> typename container, typename A >
poligono2D<T>::poligono2D(const container<segmento2D<T>, A>& v):
	poligono2D(v.begin(), v.end())
{
}

template<typename T>
poligono2D<T>::poligono2D(const poligono2D<T>& otro):
	vertices(otro.vertices),
	segmentos(otro.segmentos)
	{}

template<typename T>
template< template<typename> typename iterator_t >
poligono2D<T>::poligono2D(const iterator_t<punto2D<T> >& inicio, const iterator_t<punto2D<T> >& fin)
	: vertices(), segmentos()
{
	for(iterator_t<punto2D<T> > i=inicio; i!=fin; i++){
		vertices.push_back(*i);
	}
	construirSegmentos();
}

template<typename T>
void poligono2D<T>::construirSegmentos(){
	for(auto i=++vertices.begin();i!=vertices.end();i++){
		segmentos.push_back(segmento(*prev(i), *i));
	}
	//Unimos con el principio (Nos aseguramos de que el polígono es cerrado)
	segmentos.push_back(segmento(vertices.back(), vertices.front()));
}

template<typename T>
void poligono2D<T>::construirVertices(){
	for(auto it=segmentos.begin(); it!=segmentos.end(); ++it){
		vertices.push_back(it->a);
	}
}

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
