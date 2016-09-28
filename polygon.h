#ifndef _POLYGON_H
#define _POLYGON_H

#include <list>
#include <stdexcept>
#include <iostream>
#include <map>
#include <fstream>

#include "triangle.h"
#include "segment.h"
#include "point.h"

class invalidPolygon: public std::exception {
};

class polygon2d {
public:
	std::list<point2d> vertices;
	std::list<segment2d> segmentos;

public:
	void construirSegmentos();
	void construirVertices();
	bool puntoEnPoligono(point2d p, int precision=3) const;

	polygon2d();

	template< template<typename, typename> typename container, typename A >
	polygon2d(const container<point2d, A>& v);

	template< template<typename, typename> typename container, typename A >
	polygon2d(const container<segment2d, A>& v);

	template< template<typename> typename iterator_t >
	polygon2d(const iterator_t<point2d >& inicio, const iterator_t<point2d >& fin);

	template< template<typename> typename iterator_t >
	polygon2d(const iterator_t<segment2d >& inicio, const iterator_t<segment2d >& fin);

	polygon2d(const polygon2d& other);
	virtual ~polygon2d();


};

template<template<typename, typename> typename container, typename A >
polygon2d::polygon2d(const container<point2d, A>& v):
	polygon2d(v.begin(), v.end())
{
}

template<template<typename, typename> typename container, typename A >
polygon2d::polygon2d(const container<segment2d, A>& v):
	polygon2d(v.begin(), v.end())
{
}

template< template<typename> typename iterator_t >
polygon2d::polygon2d(const iterator_t<point2d >& inicio, const iterator_t<point2d >& fin)
	: vertices(), segmentos()
{
	for(iterator_t<point2d > i=inicio; i!=fin; i++){
		vertices.push_back(*i);
	}
	construirSegmentos();
}
#endif
