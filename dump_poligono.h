#ifndef _DUMP_POLIGONO_H
#define _DUMP_POLIGONO_H

#include "polygon.h"
#include <fstream>

template<typename T>
void dumpPoligono(const char* file, const poligono2D<T>& p){
    ofstream archivo;
    archivo.open(file, ofstream::out);

    for(auto v : p.vertices){
        archivo << v.x << "\t" << v.y << "\n";
    }
    archivo << p.vertices.front().x << "\t" << p.vertices.front().y << "\n\n";
    archivo.close();
}


#endif
