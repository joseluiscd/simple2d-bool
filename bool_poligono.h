#include "poligono.h"
#include <list>

#ifndef _BOOL_POLIGONO_H
#define _BOOL_POLIGONO_H

template<typename T>
list<pair<punto2D<T>, list<segmento2D<T> >::iterator > > puntosDeCorte(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	typedef typename list<segmento2D<T> >::iterator iterador;
	typedef typename list<pair<punto2D<T>, list<segmento2D<T> >::iterator > >::iterator iteradorp;
	typedef typename list<pair<punto2D<T>, list<segmento2D<T> >::iterator > >::reverse_iterator riteradorp;

	list<pair<punto2D<T>, list<segmento2D<T> >::iterator > > vert1;

	for(iterador i = a.segmentos.begin(); i!= a.segmentos.end(); i++){
		list<pair<punto2D<T>, list<segmento2D<T> >::iterator > > cortes_segmento;
		for(iterador j = b.segmentos.begin(); j!=b.segmentos.end(); i++){
			if(segmentoRespectoSegmento(*i, *j, precision)==cortan){
				//calculamos el punto de corte
				cortes_segmento.push_back(make_pair(puntoCorte(*i, *j), j));
			}
		}

		if(cortes_segmento.size()>0){
			//Los puntos, por la definición del polígono están en orden. El problema es que pueden estar al revés.
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

template<typename T>
struct nodoPoligono {
	punto2D<T> punto;

	//Los puntos por los que pasan los segmentos hasta llegar al siguiente punto de corte
	list<punto2D<T> > puntosP1;
	list<punto2D<T> > puntosP2;

	nodoPoligono(const punto2D<T>& _punto=punto2D<T>()): punto(_punto), puntosP1(), puntosP2() {};

}

template<typename T>
class boolPoligono {
private:
	list<nodoPoligono*> puntos;
	const poligono2D<T>& p1;
	const poligono2D<T>& p2;
	//Flag que indica si el polígono 2 tenemos que procesarlo al revés
	bool p2c;

	//Construir hasta el primer punto de corte. Este método se encarga de
	//decidir si el polígono 2 hay que procesarlo al revés
	void construyePrimero((list<pair<punto2D<T>, segmento2D<T> > > pdc, int precision=3);
public:
	boolPoligono(const poligono2D<T>& p1, const poligono2D<T>& p2, int precision=3);
}

template<typename T>
void construyePrimero(list<pair<punto2D<T>, segmento2D<T> > >& pdc, int precision){
	auto primero = pdc.front();
	auto sigPunto = *(++pdc.begin()).first;

	/*
	Se construye la combinación de los polígonos, usando el mismo sentido del polígono 1.
	Como no sabemos qué sentido tendrá el 2º respecto al primero, lo construimos 2 veces
	y utilizaremos en sucesivas operaciones aquel sentido que se corresponda.
	*/

	nodoPoligono* sentidoNormal = new nodoPoligono(p);
	nodoPoligono* sentidoContrario = new nodoPoligono(p);
	nodoPoligono* definitivo = NULL; //Aún no sabemos cuál se escoge

	auto segmentoSNormal = primero.second;
	auto segmentoSContrario = primero.second;

	while(true){
		if(puntoEnSegmento(sigPunto, *segmentoSNormal)){
			p2c = false;

			sentidoNormal.puntosP2.push_back(sigPunto);
			definitivo = sentidoNormal;
			delete sentidoContrario;
			break;
		} else if(puntoEnSegmento(sigPunto, *segmentoSContrario)){
			parada = true;
			p2c = true;

			sentidoContrario.puntosP2.push_back(sigPunto);
			definitivo = sentidoContrario;
			delete sentidoNormal;
			break;
		}

		sentidoNormal.puntosP2.push_back(segmentoSNormal->b);
		sentidoContrario.puntosP2.push_back(segmentoSContrario->a);

		segmentoSNormal++;
		segmentoSContrario--;

	}

	//Ya sabemos el sentido definitivo del polígono 2, y hemos introducido los
	//vértices, ahora introducimos los del polígono 1
	auto segmentoP1 = p1.segmentos.begin();
	while(true){
		if(puntoEnSegmento(sigPunto, *segmentoP1)){
			definitivo.puntosP1.push_back(sigPunto);
			break;
		}
		definitivo.puntosP1.push_back(segmentoP1->b);
		segmentoP1++;
	}

	puntos.push_back(definitivo);
	pdc.pop_front();

}

template<typename T>
void construyeSiguientes(list<pair<punto2D<T>, segmento2D<T> > > pdc, int precision){
	//TODO: Seguir por aquí
}

template<typename T>
boolPoligono<T>::boolPoligono(const poligono2D<T>& _p1, const poligono2D<T>& _p2, int precision)
	:p2c(false), puntos(), p1(_p1), p2(_p2)
{
	list<pair<punto2D<T>, segmento2D<T> > > pdc = puntosDeCorte(p1, p2, precision);
	construyePrimero(pdc, precision);
}
#endif
