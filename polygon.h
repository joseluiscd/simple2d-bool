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
	template< template<class, class> class container, class A >
	polygon2d(const container<point2d, A>& v);

	template< template<class> class iterator_t >
	polygon2d(const iterator_t<point2d >& start, const iterator_t<point2d >& end);

	polygon2d(const polygon2d& other);
	virtual ~polygon2d();


};

template<template<class, class> class container, class A >
polygon2d::polygon2d(const container<point2d, A>& v):
	polygon2d(v.begin(), v.end())
{
}

template< template<class> class iterator_t >
polygon2d::polygon2d(const iterator_t<point2d >& start, const iterator_t<point2d >& end)
	: vertices(), segments()
{
	for(iterator_t<point2d > i=start; i!=end; i++){
		vertices.push_back(*i);
	}
	buildSegments();
}
#endif
