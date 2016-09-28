#include <vector>
#include "polygon.h"

#ifndef _LOADER_POLIGONO_H
#define _LOADER_POLIGONO_H

vector<poligono2Df>* cargarFicheroMif_float(const char* fichero, int precision);
vector<poligono2Dd>* cargarFicheroMif_double(const char* fichero, int precision);

poligono2D<float>* cargarFicheroFloat(const char* fichero);

#endif
