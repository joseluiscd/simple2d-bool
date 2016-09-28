#include <list>
#include <cmath>
#include "polygon.h"
#include "point.h"

#define PI 3.14159265

polygon2d* poligonoRandom(float radio, float ruido, int npuntos){
    std::list<point2d> puntos;
    float paso = (2*PI)/npuntos;

    for(int i=0;i<npuntos;i++){
        float random = ruido*(((rand()%1000)+1)/1000.0);

        float x = (random + radio) * cos(paso*i);
        float y = (random + radio) * sin(paso*i);
        puntos.push_back(point2d(x,y));
    }

    return new polygon2d(puntos);
}
