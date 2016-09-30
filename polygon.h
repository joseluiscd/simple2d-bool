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
public:
	std::list<point2d> vertices;
	std::list<segment2d> segmentos;

public:
	void construirSegmentos();
	void construirVertices();
	inclusionResult puntoEnPoligono(point2d p, int precision=3) const;

	polygon2d();

	/*
	Load polygon using a generic container with points, which are the polygon's vertices
	@param container The container with the vertices
	*/
	template< template<class, class> class container, class A >
	polygon2d(const container<point2d, A>& v);

	/*
	Load polygon using a generic container with segments
	@param container The container with the segments
	*/
	template< template<class, class> class container, class A >
	polygon2d(const container<segment2d, A>& v);

	template< template<class> class iterator_t >
	polygon2d(const iterator_t<point2d >& inicio, const iterator_t<point2d >& fin);

	template< template<class> class iterator_t >
	polygon2d(const iterator_t<segment2d >& inicio, const iterator_t<segment2d >& fin);

	polygon2d(const polygon2d& other);
	virtual ~polygon2d();


};

template<template<class, class> class container, class A >
polygon2d::polygon2d(const container<point2d, A>& v):
	polygon2d(v.begin(), v.end())
{
}

template<template<class, class> class container, class A >
polygon2d::polygon2d(const container<segment2d, A>& v):
	polygon2d(v.begin(), v.end())
{
}

template< template<class> class iterator_t >
polygon2d::polygon2d(const iterator_t<point2d >& inicio, const iterator_t<point2d >& fin)
	: vertices(), segmentos()
{
	for(iterator_t<point2d > i=inicio; i!=fin; i++){
		vertices.push_back(*i);
	}
	construirSegmentos();
}
#endif
