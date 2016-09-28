#ifndef _RECONSTRUCCION_H
#define _RECONSTRUCCION_H

#include <vector>
#include <list>

#include "polygon.h"

std::vector<polygon2d* >* reconstruye(const std::vector<segment2d >& segmentos, int precision=3);

#endif
