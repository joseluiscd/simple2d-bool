#include "poligono.h"
#include "punto.h"
#include "bool_poligono.h"
#include <list>
#include <iostream>
#include <cstdlib>
#include "dump_poligono.h"
#include "loader_poligono.h"

using namespace std;
int main(int argc, char* argv[]) {
    if(argc!=3){
        puts("Se necesitan 2 argumentos (ficheros con polígonos)");
        exit(0);
    }
    poligono2Df* poligono1 = cargarFicheroFloat(argv[1]);
    poligono2Df* poligono2 = cargarFicheroFloat(argv[2]);

    auto x = diferenciaPoligonos(*poligono1, *poligono2);

    for(auto i : *x){
        printf("%f\t%f\t%f\t%f\n", i.a.x, i.a.y, i.b.x, i.b.y);
    }
    return 0;
}
