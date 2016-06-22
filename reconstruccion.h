#ifndef _RECONSTRUCCION_H
#define _RECONSTRUCCION_H

#include <vector>
#include <list>
#include "poligono.h"

using namespace std;

template<typename T>
vector<poligono2D<T>* >* reconstruye(const vector<segmento2D<T> >& segmentos, int precision=3){
    vector<poligono2D<T>* >* ret = new vector<poligono2D<T>* >();
    list<segmento2D<T> > restantes(segmentos.begin(), segmentos.end());

    //Eliminamos los puntos
    for(auto it=restantes.begin(); it!=restantes.end(); it++){
        if(signo(distanciaCuadrado(it->b, it->a), precision)==0){
            //Es un punto
            it = prev(restantes.erase(it));
        }
    }

    while(!restantes.empty()){
        list<punto2D<T> > puntos;
        segmento2D<T> current = restantes.front();
        segmento2D<T> primero = current;

        restantes.pop_front();

        puntos.push_back(current.a);
        bool parada=false;
        while(!parada){
            auto candidato = restantes.end();
            T coseno = -1;
            for(auto it=restantes.begin(); it!=restantes.end(); it++){
                if(signo(distanciaCuadrado(current.b, it->a), precision)==0){
                    if(candidato==restantes.end()){
                        candidato = it;
                    } else {
                        //Comprobamos el ángulo
                        T c = cosenoAngulo(reves(current), *it);
                        int o = orientacion(reves(current), *it);
                        if((o==-1 || o==0) && c>coseno){
                            candidato = it;
                            coseno = c;
                        }
                    }

                }
            }

            //Ya tenemos el candidato definitivo para formar parte de nuestro polígono
            puntos.push_back(candidato->a);
            current = *candidato;

            if(signo(distanciaCuadrado(current.b, primero.a), precision)==0){
                parada = true;
                try{
                    ret->push_back(new poligono2D<T>(puntos));
                } catch(poligonoInvalido& e){
                    //TODO: No ignorar la excepción, comprobar qué pasa exactamente
                }
                puntos.clear();
            }

            restantes.erase(candidato);

        }

    }

    return ret;
}

#endif
