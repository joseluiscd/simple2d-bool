#ifndef _RECONSTRUCCION_H
#define _RECONSTRUCCION_H

template<typename T>
vector<poligono2D<T>* >* reconstruye(const vector<segmento2D<T> >& segmentos, int precision=3){
    vector<poligono2D<T>* >* ret = new vector<poligono2D<T>* >();
    list<segmento2D<T>& restantes(segmentos.begin(), segmentos.end());

    //Este bucle se ejecutará tantas veces como polígonos existan
    while(!restantes.empty()){
        list<punto2D<T> > puntos;
        segmento2D<float> current = restantes.front();
        segmento2D<float> primero = current;
        restantes.pop_front();

        puntos.push_back(current.a);

        bool parada = false;
        auto it=restantes.begin();
        while(!parada){
            /*
            Este bucle recorre circularmente la lista de segmentos restantes,
            comprobando si van conectando. Cuando el polígono se cierra, lo añade
            para devolver
            */
            if(it==restantes.end()){
                it=restantes.begin();
            }

            if(signo(distanciaCuadrado(current.b, it->a), precision)==0){
                //Coinciden
                current = *it; //Actualizamos el actual
                it = restantes.erase(it);
                puntos.push_back(current.a);

                if(signo(distanciaCuadrado(current.b, primero.a), precision)==0){
                    //Cerramos polígono
                    ret->push_back(new poligono2D<float>(puntos));
                    puntos.clear();
                    parada = true;
                }

            } else {
                it++;
            }
        }
    }

    return ret;
}

#endif
