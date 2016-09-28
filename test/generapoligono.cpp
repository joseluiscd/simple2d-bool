#include "polygon.h"
#include "random_polygon.h"

int main(int argc, char* argv[]){
    if(argc!=3){
        puts("Error, se requieren 2 argumentos: (ruido y número de lados)");
        exit(1);
    }
    srand(time(0));

    float ruido = atof(argv[1]);
    int lados = atoi(argv[2]);

    poligono2D<float>* x = poligonoRandom(1, ruido, lados);
    for(auto i : x->vertices){
        printf("%f\t%f\n", i.x, i.y);
    }
    return 0;
}
