#include "dump_polygon.h"

void dumpPoligono(const char* file, const polygon2d& p){
    std::ofstream archivo;
    archivo.open(file, std::ofstream::out);

    for(auto v : p.vertices){
        archivo << v.x << "\t" << v.y << "\n";
    }
    archivo << p.vertices.front().x << "\t" << p.vertices.front().y << "\n\n";
    archivo.close();
}
