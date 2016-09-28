#ifndef _LOADER_POLIGONO_H
#define _LOADER_POLIGONO_H

#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <iostream>
#include <vector>

#include "polygon.h"
#include "point.h"


std::vector<polygon2d>* cargarFicheroMif(const char* fichero, int precision);
polygon2d* cargarFicheroFloat(const char* fichero);

#endif
