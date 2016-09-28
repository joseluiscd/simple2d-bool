#include "loader_polygon.h"

using namespace std;

std::vector<polygon2d>* cargarFicheroMif(const char* fichero, int precision){
	ifstream fich(fichero);
	string linea;
	vector<polygon2d >* poligonos = new vector<polygon2d >();
	bool datos = false;
	char descarta;
	double x1, y1, x2, y2;

	int npuntos_restantes=0;
	list<point2d >* puntos = NULL;
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
				double x,y;
				stringstream ss(linea);
				ss>>ws>>x>>ws>>y;
				point2d leido(x,y);
				point2d punt = cambiaCoordenadas(leido, x1, y1, x2, y2, precision);
				puntos->push_back(punt);
				npuntos_restantes--;
			} else if(linea.find("Region")==0){ //Comienza un polígono...
				fich>>npuntos_restantes>>ws;
				if(puntos){
					poligonos->push_back(polygon2d(*puntos));
					delete puntos;
				}

				puntos = new list<point2d >();
			}
		}
	}

	if(puntos){
		poligonos->push_back(polygon2d(*puntos));
		delete puntos;
	}


	return poligonos;
}

polygon2d* cargarFicheroFloat(const char* fichero){
    ifstream fich(fichero);
	string linea;
	polygon2d* ret;

	list<point2d > puntos;
	while(getline(fich, linea)){
		float x,y;
		stringstream ss(linea);
		ss>>ws>>x>>ws>>y;
		puntos.push_back(point2d(x,y));
	}

	ret = new polygon2d(puntos);
	return ret;
}
