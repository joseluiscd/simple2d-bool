#include "dump_polygon.h"

void dumpPolygon(const char* file, const polygon2d& p){
    std::ofstream filestream;
    filestream.open(file, std::ofstream::out);

    for(auto v : p.vertices){
        filestream << v.x << "\t" << v.y << "\n";
    }
    filestream << p.vertices.front().x << "\t" << p.vertices.front().y << "\n\n";
    filestream.close();
}
