#include "poligono.h"
#include "loader_poligono.h"
#include "punto.h"
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
			cout<<"Línea de cabecera"<<endl;
			if(linea.find("Data")==0){ //Comenzamos a leer datos a la próxima
				cout<<"A la siguiente, datos"<<endl;
				datos = true;
			} else if(linea.find("CoordSys")==0){ // Sólo nos interesan los bounds
				cout<<"Vamos a leer los bordes"<<endl;
				int pos = linea.find("Bounds ");
				string bounds = linea.substr(pos+7);
				stringstream ss(bounds);
				ss>>ws>>descarta>>x1>>ws>>descarta>>ws>>y1>>ws>>descarta>>ws>>descarta>>ws>>x2>>ws>>descarta>>ws>>y2>>descarta;
				cout<<"Bordes detectados: "<<x1<<","<<y1<<" / "<<x2<<","<<y2<<endl;
			}
		} else { //Leer datos

			if(npuntos_restantes>1){ //Tenemos puntos para seguir leyendo
				T x,y;
				stringstream ss(linea);
				ss>>ws>>x>>ws>>y;
				cout<<"Leyendo un punto: "<<x<<","<<y<<endl;
				punto2D<T> leido(x,y);
				punto2D<T> punt = cambiaCoordenadas(leido, x1, y1, x2, y2, precision);
				puntos->push_back(punt);
				npuntos_restantes--;
			} else if(linea.find("Region")==0){ //Comienza un polígono...
				cout<<"Nuevo polígono"<<endl;
				fich>>npuntos_restantes>>ws;
				cout<<npuntos_restantes<<" puntos restantes\n";
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
