#include "reconstruction.h"

using namespace std;

vector<polygon2d* >* reconstruye(const vector<segment2d >& segmentos, int precision){
    vector<polygon2d* >* ret = new vector<polygon2d* >();
    list<segment2d > restantes(segmentos.begin(), segmentos.end());

    //Eliminamos los puntos
    for(auto it=restantes.begin(); it!=restantes.end(); it++){
        if(sign(squaredDistance(it->b, it->a), precision)==0){
            //Es un punto
            it = prev(restantes.erase(it));
        }
    }

    while(!restantes.empty()){
        list<point2d > puntos;
        segment2d current = restantes.front();
        segment2d primero = current;

        restantes.pop_front();

        puntos.push_back(current.a);
        bool parada=false;
        while(!parada){
            auto candidato = restantes.end();
            double coseno = -1;
            for(auto it=restantes.begin(); it!=restantes.end(); it++){
                if(sign(squaredDistance(current.b, it->a), precision)==0){
                    if(candidato==restantes.end()){
                        candidato = it;
                    } else {
                        //Comprobamos el ángulo
                        double c = cosenoAngulo(reves(current), *it);
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

            if(sign(squaredDistance(current.b, primero.a), precision)==0){
                parada = true;
                ret->push_back(new polygon2d(puntos));

                puntos.clear();
            }

            restantes.erase(candidato);

        }

    }

    return ret;
}
