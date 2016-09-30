#include "point.h"
#include "triangle.h"
#include "segment.h"
#include "polygon.h"
#include "loader_polygon.h"
#include "bool_polygon.h"

#include <algorithm>
#include <iostream>

#include "math.h"
using namespace std;

int main(int argc, char *argv[]){
	// Probaturas
	point2d a (4.12345, 3.23456);
	point2d f = changeCoordinateSystem(a, 2.0, 2.0, 6.0, 6.0, 3);

	cout<<f.x<<","<<f.y<<endl;


	cout<<doubleSignedArea(point2d(1,3),point2d(2,4),point2d(7,5))<<endl;

	cout<<segmentRelativeToSegment(segment2d(0,1,0,1),segment2d(1,0,1,0))<<endl;


	point2d puntos[] = {point2d(0,0), point2d(1,0), point2d(1,1), point2d(0,1), point2d(5,5)};
	list<point2d> vert(puntos, puntos + sizeof(puntos) / sizeof(point2d));
	polygon2d pol(vert.begin(), vert.end());
	cout<<pol.pointInPolygon(point2d(1,1.0001),1)<<endl;


	//vector<polygon2d>* mun1 = cargarFicheroMif("datos/municipio1.mif", 9);
	//vector<polygon2d>* mun2 = cargarFicheroMif("datos/municipio2.mif", 9);


}
