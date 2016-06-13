#include "poligono.h"
#include <list>


#ifndef _BOOL_POLIGONO_H
#define _BOOL_POLIGONO_H


template<typename T>
list<punto2D<T> > puntosDeCorte(poligono2D<T> a, poligono2D<T> b, int precision=3){
	typedef typename list<segmento2D<T> >::iterator iterador;
	typedef typename list<punto2D<T> >::iterator iteradorp;
	typedef typename list<punto2D<T> >::reverse_iterator riteradorp;

	list<punto2D<T> > vert1;

	for(iterador i = a.segmentos.begin(); i!= a.segmentos.end(); i++){
		vert1.push_back(i->a);
		list<punto2D<T> > cortes_segmento;
		for(iterador j = b.segmentos.begin(); j!=b.segmentos.end(); i++){
			if(segmentoRespectoSegmento(*i, *j, precision)==cortan){
				//calculamos el punto de corte
				cortes_segmento.push_back(puntoCorte(*i, *j));
			}
		}

		if(cortes_segmento.size()>0){
			//Los puntos, por la definición del polígono están en orden. El problema es que pueden estarlo al revés.
			bool reves = distanciaCuadrado(cortes_segmento.front(), vert1.back())>distanciaCuadrado(cortes_segmento.back(), vert1.back()); //Empezamos por atrás??
			if(reves){
				for(riteradorp j=cortes_segmento.rbegin();j!=cortes_segmento.rend();j++){
					vert1.push_back(*j);
				}
			} else {
				for(iteradorp j=cortes_segmento.begin();j!=cortes_segmento.end();j++){
					vert1.push_back(*j);
				}
			}
		}
	}

	return vert1;
}

#endif
