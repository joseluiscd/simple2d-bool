#ifndef _RECONSTRUCCION_H
#define _RECONSTRUCCION_H

#include <vector>
#include <list>

#include "polygon.h"

std::vector<polygon2d* >* rebuildPolygonsFromSegments(const std::vector<segment2d >& segments, int precision=3);

#endif
