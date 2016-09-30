#include "polygon.h"
#include "point.h"
#include "bool_polygon.h"
#include <list>
#include <iostream>
#include <cstdlib>
#include "dump_polygon.h"
#include "loader_polygon.h"

using namespace std;
int main() {
    list<point2d> cuadrado1;
    list<point2d> cuadrado2;

    cuadrado1.push_back(point2d(1, 1));
    cuadrado1.push_back(point2d(1, -1));
    cuadrado1.push_back(point2d(-1, -1));
    cuadrado1.push_back(point2d(-1, 1));

    cuadrado2.push_back(point2d(0, 0));
    cuadrado2.push_back(point2d(2, 0));
    cuadrado2.push_back(point2d(2, 2));
    cuadrado2.push_back(point2d(0, 2));

    polygon2d poligono1(cuadrado1);
    polygon2d poligono2(cuadrado2);

    auto x = polygonUnion(poligono1, poligono2);

    for(auto i : *x){
        printf("%f\t%f\t%f\t%f\n", i.a.x, i.a.y, i.b.x, i.b.y);
    }
    return 0;
}
