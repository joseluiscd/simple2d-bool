#include "poligono.h"
#include "point.h"
#include "bool_poligono.h"
#include <list>
#include <iostream>
#include <cstdlib>
#include "dump_poligono.h"

using namespace std;
int main() {
    list<punto2Df> cuadrado1;
    list<punto2Df> cuadrado2;

    cuadrado1.push_back(punto2Df(1, 1));
    cuadrado1.push_back(punto2Df(1, -1));
    cuadrado1.push_back(punto2Df(-1, -1));
    cuadrado1.push_back(punto2Df(-1, 1));

    cuadrado2.push_back(punto2Df(0, 0));
    cuadrado2.push_back(punto2Df(2, 0));
    cuadrado2.push_back(punto2Df(2, 2));
//    cuadrado2.push_back(punto2Df(0, 2));

    poligono2Df poligono1(cuadrado1);
    poligono2Df poligono2(cuadrado2);

    auto x = diferenciaPoligonos(poligono1, poligono2);

    for(auto i : *x){
        printf("%f\t%f\t%f\t%f\n", i.a.x, i.a.y, i.b.x, i.b.y);
    }
    return 0;
}
