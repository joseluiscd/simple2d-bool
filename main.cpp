#include "punto.h"
#include "triangulo.h"
#include "segmento.h"
#include "signo.h"
#include "poligono.h"
#include "loader_poligono.h"
#include "bool_poligono.h"

#include <algorithm>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
	// Probaturas
	punto2Dd a (4.12345, 3.23456);
	punto2Dd f = cambiaCoordenadas(a, 2.0, 2.0, 6.0, 6.0, 3);

	cout<<f.x<<","<<f.y<<endl;


	cout<<areaSignada(punto2Dd(1,3),punto2Dd(2,4),punto2Dd(7,5))<<endl;

	cout<<segmentoRespectoSegmento(segmento2Df(0,1,0,1),segmento2Df(1,0,1,0))<<endl;

	punto2Dd asdf(0,0);
	triangulo2Dd t(punto2Dd(0, 0), punto2Dd(0,1), punto2Dd(1,0));
	if(puntoDentroDeTriangulo(t, asdf)){
		cout<<"Queueueueueueuee!!"<<endl;
	}

	punto2Df puntos[] = {punto2Df(0,0), punto2Df(1,0), punto2Df(1,1), punto2Df(0,1), punto2Df(5,5)};
	list<punto2Df> vert(puntos, puntos + sizeof(puntos) / sizeof(punto2Df));
	poligono2Df pol(vert);
	cout<<pol.puntoEnPoligono(punto2Df(1,1.0001),1)<<endl;


	vector<poligono2Dd>* mun1 = cargarFicheroMif_double("datos/municipio1.mif", 9);
	vector<poligono2Dd>* mun2 = cargarFicheroMif_double("datos/municipio2.mif", 9);

	
}
