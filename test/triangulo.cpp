#include <list>
#include <vector>
#include "reconstruction.h"
#include "polygon.h"
#include "bool_polygon.h"

using namespace std;

polygon2d* subtriangulo(polygon2d* triangulo){
    list<point2d > puntos;
    for(auto s: triangulo->segmentos){
        puntos.push_back(puntoMedio(s));
    }

    return new polygon2d(puntos);
}

list<polygon2d* > triangulo(int iterations){
    list<polygon2d* > cola;

    list<point2d > primero;
    primero.push_back(point2d(0, 1));
    primero.push_back(point2d(-1, -1));
    primero.push_back(point2d(1, -1));

    cola.push_back(new polygon2d(primero));

    for(int i=0; i<iterations; i++){
        polygon2d* actual = cola.front();
        cola.pop_front();

        polygon2d* resta = subtriangulo(actual);
        vector<segment2d >* segmentos = diferenciaPoligonos(*actual, *resta);
        vector<polygon2d* >* nuevos = reconstruye(*segmentos);

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
