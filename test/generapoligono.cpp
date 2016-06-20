#include "poligono.h"
#include "random_poligono.h"

int main(){
    srand(time(0));
    poligono2D<float>* x = poligonoRandom(1, 0.1, 100);
    for(auto i : x->vertices){
        printf("%f\t%f\n", i.x, i.y);
    }
    return 0;
}
