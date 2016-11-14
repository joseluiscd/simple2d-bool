#ifndef _POLYGON_H
#define _POLYGON_H

#include <list>
#include <stdexcept>
#include <iostream>
#include <map>
#include <fstream>
#include <string>

#include "triangle.h"
#include "segment.h"
#include "point.h"

class invalidPolygon: public std::exception {
private:
	const char* what_str;
public:
	invalidPolygon(const char* _what="Invalid polygon"): what_str(_what) {};

	const char* what() const noexcept {
		return what_str;
	}

};

class polygon2d {
private:
	double minX, minY, maxX, maxY; //Bounding box

public:
	std::list<point2d> vertices;
	std::list<segment2d> segments;

public:
	void buildSegments();
	inclusionResult pointInPolygon(point2d p, int precision=3) const;

	polygon2d();

	/**
	Load polygon using a generic container with points, which are the polygon's vertices
	@param container The container with the vertices
	*/
	template< class container >
	polygon2d(const container& v);

	template< class iterator_t >
	polygon2d(const iterator_t& start, const iterator_t& end);


	polygon2d(const polygon2d& other);
	virtual ~polygon2d();


};

template<class container>
polygon2d::polygon2d(const container& v):
	polygon2d(v.begin(), v.end())
{
}

template< class iterator_t >
polygon2d::polygon2d(const iterator_t& start, const iterator_t& end)
	: vertices(), segments()
{
	for(iterator_t i=start; i!=end; i++){
		vertices.push_back(*i);
	}
	buildSegments();
}

inclusionResult pointInPolygon(const point2d& point, const polygon2d& polygon, int precision=3);
#endif
