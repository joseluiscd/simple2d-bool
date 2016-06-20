#include "poligono.h"
#include "punto.h"
#include "bool_poligono.h"
#include <list>
#include <iostream>
#include <cstdlib>
#include "dump_poligono.h"
#include "loader_poligono.h"

using namespace std;
int main() {
    list<punto2Df> cuadrado1;
    list<punto2Df> cuadrado2;

    poligono2Df* poligono1 = cargarFicheroFloat("pol1.txt");
    poligono2Df* poligono2 = cargarFicheroFloat("pol2.txt");

    auto x = unionPoligonos(*poligono1, *poligono2);

    for(auto i : *x){
        printf("%f\t%f\t%f\t%f\n", i.a.x, i.a.y, i.b.x, i.b.y);
    }
    return 0;
}
