#include "poligono.h"
#include "loader_poligono.h"
#include "point.h"
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <iostream>

using namespace std;

template<typename T>
vector<poligono2D<T> >* cargarFicheroMif(const char* fichero, int precision, T tipo){ // La variable tipo sólo sirve para identificar la función como float o double
	ifstream fich(fichero);
	string linea;
	vector<poligono2D<T> >* poligonos = new vector<poligono2D<T> >();
	bool datos = false;
	char descarta;
	T x1, y1, x2, y2;

	int npuntos_restantes=0;
	list<punto2D<T> >* puntos = NULL;
	while(!fich.eof()){
		getline(fich, linea);
		if(!datos){ //Leer cabecera
			if(linea.find("Data")==0){ //Comenzamos a leer datos a la próxima
				datos = true;
			} else if(linea.find("CoordSys")==0){ // Sólo nos interesan los bounds
				int pos = linea.find("Bounds ");
				string bounds = linea.substr(pos+7);
				stringstream ss(bounds);
				ss>>ws>>descarta>>x1>>ws>>descarta>>ws>>y1>>ws>>descarta>>ws>>descarta>>ws>>x2>>ws>>descarta>>ws>>y2>>descarta;
			}
		} else { //Leer datos
			if(npuntos_restantes>1){ //Tenemos puntos para seguir leyendo
				T x,y;
				stringstream ss(linea);
				ss>>ws>>x>>ws>>y;
				punto2D<T> leido(x,y);
				punto2D<T> punt = cambiaCoordenadas(leido, x1, y1, x2, y2, precision);
				puntos->push_back(punt);
				npuntos_restantes--;
			} else if(linea.find("Region")==0){ //Comienza un polígono...
				fich>>npuntos_restantes>>ws;
				if(puntos){
					poligonos->push_back(poligono2D<T>(*puntos));
					delete puntos;
				}

				puntos = new list<punto2D<T> >();
			}
		}
	}

	if(puntos){
		poligonos->push_back(poligono2D<T>(*puntos));
		delete puntos;
	}


	return poligonos;
}

vector<poligono2Df>* cargarFicheroMif_float(const char* fichero, int precision){
	return cargarFicheroMif(fichero, precision, (float)1);
}

vector<poligono2Dd>* cargarFicheroMif_double(const char* fichero, int precision){
	return cargarFicheroMif(fichero, precision, (double)1);
}

poligono2D<float>* cargarFicheroFloat(const char* fichero){
    ifstream fich(fichero);
	string linea;
	poligono2D<float>* ret;

	list<punto2D<float> > puntos;
	while(getline(fich, linea)){
		float x,y;
		stringstream ss(linea);
		ss>>ws>>x>>ws>>y;
		puntos.push_back(punto2D<float>(x,y));
	}

	ret = new poligono2D<float>(puntos);
	return ret;
}
