#include <list>
#include <vector>
#include "reconstruccion.h"
#include "poligono.h"
#include "bool_poligono.h"

using namespace std;

poligono2D<float>* subtriangulo(poligono2D<float>* triangulo){
    list<punto2D<float> > puntos;
    for(auto s: triangulo->segmentos){
        puntos.push_back(puntoMedio(s));
    }

    return new poligono2D<float>(puntos);
}

list<poligono2D<float>* > triangulo(int iterations){
    list<poligono2D<float>* > cola;

    list<punto2D<float> > primero;
    primero.push_back(punto2D<float>(0, 1));
    primero.push_back(punto2D<float>(-1, -1));
    primero.push_back(punto2D<float>(1, -1));

    cola.push_back(new poligono2D<float>(primero));

    for(int i=0; i<iterations; i++){
        poligono2D<float>* actual = cola.front();
        cola.pop_front();

        poligono2D<float>* resta = subtriangulo(actual);
        vector<segmento2D<float> >* segmentos = diferenciaPoligonos(*actual, *resta);
        vector<poligono2D<float>* >* nuevos = reconstruye(*segmentos);

        delete resta;
        delete segmentos;
        delete actual;

        for(int i=0;i<nuevos->size();i++){
            cola.push_back(nuevos->at(i));
        }

    }

    return cola;
}

int main(int argc, char* argv[]){
    if(argc!=2){
        puts("Se requiere como argumento el número de iteraciones");
        exit(1);
    }

    int its = atoi(argv[1]);

    auto x = triangulo(its);
    for(auto pol: x){
        for(auto vert: pol->vertices){
            printf("%f\t%f\n", vert.x, vert.y);
        }
        printf("\n");
    }
}
