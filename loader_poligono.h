#include <vector>
#include "poligono.h"

#ifndef _LOADER_POLIGONO_H
#define _LOADER_POLIGONO_H

vector<poligono2Df>* cargarFicheroMif_float(const char* fichero, int precision);
vector<poligono2Dd>* cargarFicheroMif_double(const char* fichero, int precision);

#endif
