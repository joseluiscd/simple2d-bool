#include "poligono.h"
#include <list>
#include <vector>

#ifndef _BOOL_POLIGONO_H
#define _BOOL_POLIGONO_H


template<typename T>
list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > > puntosDeCorte(const poligono2D<T>& a, const poligono2D<T>& b, int precision=3){
	list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > > vert1;
	for(auto i = a.segmentos.begin(); i != a.segmentos.end(); i++){
		list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > > cortes_segmento;
		for(auto j = b.segmentos.begin(); j!=b.segmentos.end(); j++){
			if(segmentoRespectoSegmento(*i, *j, precision)==cortan){
				//calculamos el punto de corte
				printf("(%f,%f - %f,%f)\n", i->a.x, i->a.y, i->b.x, i->b.y);
				printf("(%f,%f - %f,%f)\n\n", j->a.x, j->a.y, j->b.x, j->b.y);
				cortes_segmento.push_back(make_pair(puntoCorte(*i, *j), j));
				printf("Done!\n");
			}
		}

		if(cortes_segmento.size()>0){
			//Los puntos, por la definición del polígono están en orden. El problema es que pueden estar al revés.
			bool reves = distanciaCuadrado(cortes_segmento.front().first, vert1.back().first)>distanciaCuadrado(cortes_segmento.back().first, vert1.back().first); //Empezamos por atrás??
			if(reves){
				for(auto j=cortes_segmento.rbegin();j!=cortes_segmento.rend();j++){
					vert1.push_back(*j);
				}
			} else {
				for(auto j=cortes_segmento.begin();j!=cortes_segmento.end();j++){
					vert1.push_back(*j);
				}
			}
		}
	}

	return vert1;
}

template<typename T>
struct nodoPoligono {
	const punto2D<T> punto;

	//Los puntos por los que pasan los segmentos hasta llegar al siguiente punto de corte
	list<punto2D<T> > puntosP1;
	list<punto2D<T> > puntosP2;

	nodoPoligono(const punto2D<T>& _punto=punto2D<T>()): punto(_punto), puntosP1(), puntosP2() {};

};

/*
Estructura auxiliar para realizar después las operaciones booleanas entre polígonos
*/
template<typename T>
class boolPoligono {
private:
	list<nodoPoligono<T>*> puntos;
	const poligono2D<T>& p1;
	const poligono2D<T>& p2;

	//Flag que indica si el polígono 2 tenemos que procesarlo al revés
	bool p2c;

	//Construir hasta el primer punto de corte. Este método se encarga de
	//decidir si el polígono 2 hay que procesarlo al revés
	void construyePrimero(list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > >& pdc, int precision=3);
	void construyeSiguientes(list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > >& pdc, int precision=3);
public:
	boolPoligono(const poligono2D<T>& p1, const poligono2D<T>& p2, int precision=3);

	vector<poligono2D<T> >* interseccion() const;
};

template<typename T>
void boolPoligono<T>::construyePrimero(list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > >& pdc, int precision){
	auto primero = pdc.front();
	auto sigPunto = (++pdc.begin())->first;

	/*
	Se construye la combinación de los polígonos, usando el mismo sentido del polígono 1.
	Como no sabemos qué sentido tendrá el 2º respecto al primero, lo construimos 2 veces
	y utilizaremos en sucesivas operaciones aquel sentido que se corresponda.
	*/

	nodoPoligono<T>* sentidoNormal = new nodoPoligono<T>(primero.first);
	nodoPoligono<T>* sentidoContrario = new nodoPoligono<T>(primero.first);
	nodoPoligono<T>* definitivo = NULL; //Aún no sabemos cuál se escoge

	auto segmentoSNormal = primero.second;
	auto segmentoSContrario = primero.second;

	while(true){
		if(puntoEnSegmento(sigPunto, *segmentoSNormal)){
			p2c = false;

			sentidoNormal->puntosP2.push_back(sigPunto);
			definitivo = sentidoNormal;
			delete sentidoContrario;
			break;
		} else if(puntoEnSegmento(sigPunto, *segmentoSContrario)){
			p2c = true;

			sentidoContrario->puntosP2.push_back(sigPunto);
			definitivo = sentidoContrario;
			delete sentidoNormal;
			break;
		}

		sentidoNormal->puntosP2.push_back(segmentoSNormal->b);
		sentidoContrario->puntosP2.push_back(segmentoSContrario->a);

		segmentoSNormal++;
		segmentoSContrario--;

	}

	//Ya sabemos el sentido definitivo del polígono 2, y hemos introducido los
	//vértices, ahora introducimos los del polígono 1
	auto segmentoP1 = p1.segmentos.begin();
	while(true){
		if(puntoEnSegmento(sigPunto, *segmentoP1)){
			definitivo->puntosP1.push_back(sigPunto);
			break;
		}
		definitivo->puntosP1.push_back(segmentoP1->b);
		segmentoP1++;
	}

	puntos.push_back(definitivo);
	pdc.pop_front();

}

template<typename T>
void boolPoligono<T>::construyeSiguientes(list<pair<punto2D<T>, typename list<segmento2D<T> >::const_iterator > >& pdc, int precision){
	auto segmentoP1 = p1.segmentos.begin();

	//Llegamos al segmento de P1 donde se produce la intersección
	while(!puntoEnSegmento(pdc.front().first, *segmentoP1)) segmentoP1++;

	do {
		auto corte = pdc.front();
		punto2D<T>& punto = corte.first;
		pdc.pop_front();

		auto sigPuntoIt = pdc.begin();
		punto2D<T> sigPunto;
		if(sigPuntoIt==pdc.end()){
			//No quedan más puntos de corte. Se ejecuta la última vez
			sigPunto = puntos.front()->punto; //primer punto de corte (para cerrar)
		} else {
			//Quedan puntos de corte
			sigPunto = sigPuntoIt->first;
		}

		nodoPoligono<T>* actual = new nodoPoligono<T>(punto);

		//Introducimos los puntos del polígono 2
		auto segmentoP2 = corte.second;
		while(!puntoEnSegmento(sigPunto, *segmentoP2)){

			actual->puntosP2.push_back(
				p2c ?
				(segmentoP2--)->a :
				(segmentoP2++)->b
			);

			//Comprobamos si hay que dar la vuelta al polígono 2
			if(segmentoP2==p2.segmentos.begin()){
				segmentoP2 = p2.segmentos.end();
				segmentoP2--;
			} else if(segmentoP2==p2.segmentos.end()){
				segmentoP2 = p2.segmentos.begin();
			}
		}
		actual->puntosP2.push_back(sigPunto);

		//Introducimos los puntos del polígono 1
		while(segmentoP1!=p1.segmentos.end()){
			actual->puntosP2.push_back((segmentoP1++)->b);
		}
		actual->puntosP1.push_back(sigPunto);

		puntos.push_back(actual);
	} while(!pdc.empty());
}

template<typename T>
boolPoligono<T>::boolPoligono(const poligono2D<T>& _p1, const poligono2D<T>& _p2, int precision)
	:p2c(false), puntos(), p1(_p1), p2(_p2)
{
	printf("Construyendo polígonos...\n");
	auto pdc = puntosDeCorte(p1, p2, precision);
	printf("Ya está\n");
	construyePrimero(pdc, precision);
	construyeSiguientes(pdc, precision);
}
#endif

template<typename T>
vector<poligono2D<T> >* boolPoligono<T>::interseccion() const {
	vector<poligono2D<T> >* ret = new vector<poligono2D<T> >();

	list<punto2D<T> > poligonoActual;
	const punto2D<T>* puntoFinal;

	for(auto it=puntos.begin(); it!=puntos.end(); it++){
		punto2D<T> m1 = puntoMedio((*it)->punto, (*it)->puntosP1.front());
		punto2D<T> m2 = puntoMedio((*it)->punto, (*it)->puntosP2.front());

		//Distinguimos 3 casos
		if(p1.puntoEnPoligono(m2)){
			if(p2.puntoEnPoligono(m1)){
				//Caso 1: tenemos que elegir los 2 polígonos
				poligonoActual.push_back((*it)->punto);
				for(auto itp=(*it)->puntosP1.begin(); itp!=(*it)->puntosP1.end(); itp++){
					printf("Punto: (%f, %f)\n", itp->x, itp->y);
					poligonoActual.push_back(*itp);
				}
				for(auto itp=++((*it)->puntosP2.rbegin()); itp!=(*it)->puntosP2.rend(); itp++){
					printf("Punto(r): (%f, %f)\n", itp->x, itp->y);
					poligonoActual.push_back(*itp);
				}

				ret->push_back(poligono2D<T>(poligonoActual));
				poligonoActual.clear();
			} else {
				//Caso 2: elegimos los puntos del polígono 2
				if(!puntoFinal){
					puntoFinal = &(*it)->punto;
				}

				for(auto itp=(*it)->puntosP2.begin(); itp!=(*it)->puntosP2.end(); itp++){
					poligonoActual.push_back(*itp);
				}
			}
		} else if(p2.puntoEnPoligono(m1)){
			//Caso 3: elegimos los puntos del polígono 1
			if(!puntoFinal){
				puntoFinal = &(*it)->punto;
			}
			for(auto itp=(*it)->puntosP1.begin(); itp!=(*it)->puntosP1.end(); itp++){
				poligonoActual.push_back(*itp);
			}
		}
	}

	if(puntoFinal){
		poligonoActual.push_back(*puntoFinal);
		ret->push_back(poligono2D<T>(poligonoActual));
	}

	return ret;
}
