#include <list>
#include <cmath>
#include "poligono.h"
#include "punto.h"

#define PI 3.14159265

poligono2D<float>* poligonoRandom(float radio, float ruido, int npuntos){
    list<punto2D<float> > puntos;
    float paso = (2*PI)/npuntos;

    for(int i=0;i<npuntos;i++){
        float random = ruido*(((rand()%1000)+1)/1000.0);

        float x = random * radio * cos(paso*i);
        float y = random * radio * sin(paso*i);
        puntos.push_back(punto2D<float>(x,y));
    }

    return new poligono2D<float>(puntos);
}
