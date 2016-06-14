#include "poligono.h"
#include "punto.h"
#include "bool_poligono.h"
#include <list>
#include <iostream>

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
    cuadrado2.push_back(punto2Df(0, 2));

    poligono2Df poligono1(cuadrado1);
    poligono2Df poligono2(cuadrado2);

    cout<< "UEUE!!";
    boolPoligono<float> i(poligono1, poligono2);
    i.interseccion();

    return 0;
}
