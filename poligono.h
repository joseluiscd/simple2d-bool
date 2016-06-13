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
	bool validarPoligono();
	bool puntoEnPoligono(punto p, int precision=3);

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

	//¿Es correcto el polígono?
	if(!validarPoligono()){
		cout<<"Esto es una locura";
		throw int(2);
	}
}

// O(n^2)
template<typename T>
bool poligono2D<T>::validarPoligono(){
	//Recorremos los segmentos del polígono
	for(segmento_it i=++segmentos.begin();i!=prev(segmentos.end());i++){
		//Comprobamos si el anterior segmento coincide con el actual
		if(segmentoRespectoSegmento(*i, *prev(i))!=coinciden){
			cout<<"Encontrado un "<<segmentoRespectoSegmento(*i, *prev(i))<<endl;
			return false;
		}

		//Comprobamos si algún segmento anterior cruza con el actual
		for(segmento_it j=segmentos.begin();j!=prev(i); j++){
			if(segmentoRespectoSegmento(*i, *j)!=nada ){
				cout<<"Encontrado un (1)"<<segmentoRespectoSegmento(*i, *j)<<endl;
				return false;
			}
		}
	}

	segmento_it i = prev(segmentos.end());
	for(segmento_it j=next(segmentos.begin());j!=prev(i); j++){
		if(segmentoRespectoSegmento(*i, *j)!=nada ){
			cout<<"Encontrado un (2)"<<segmentoRespectoSegmento(*i, *j)<<endl;
			return false;
		}
	}

	//Comprobamos si el último segmento coincide con el primero (si es cerrado)
	if(segmentoRespectoSegmento(*i, *segmentos.begin())!=coinciden){
		return false;
	}
	
	cout<<"EXITO"<<endl;
	return true;
}

// O(n)
template<typename T>
bool poligono2D<T>::puntoEnPoligono(punto p, int precision){
	punto origen(0,0);
	int suma = 0;
	for(segmento_it i=segmentos.begin();i!=segmentos.end();i++){
		suma+= signo(puntoDentroDeTriangulo(triangulo2D<T>(i->a, i->b, origen),p, precision));
	}
	return suma!=0;
}


#endif
