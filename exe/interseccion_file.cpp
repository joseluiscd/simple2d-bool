#include "polygon.h"
#include "point.h"
#include "bool_polygon.h"
#include <list>
#include <iostream>
#include <cstdlib>
#include "dump_polygon.h"
#include "loader_polygon.h"
#include "reconstruction.h"

using namespace std;
int main(int argc, char* argv[]) {
    if(argc!=3){
        puts("Se necesitan 2 argumentos (ficheros con polígonos)");
        exit(0);
    }
    polygon2d* poligono1 = cargarFicheroFloat(argv[1]);
    polygon2d* poligono2 = cargarFicheroFloat(argv[2]);

    auto x = polygonIntersection(*poligono1, *poligono2);
    auto y = rebuildPolygonsFromSegments(*x);
    delete x;

    for(auto pol : *y){
        for (auto i: pol->vertices){
            printf("%f\t%f\n", i.x, i.y);
        }
        printf("\n");
    }
    return 0;
}
