
int main(int argc, char* argv[]){

}

void triangulo(int iterations){
    list<poligono2D<float>* > cola;

    list<punto2D<float> > primero;
    primero.push_back(punto2D<float>(0, 1));
    primero.push_back(punto2D<float>(-1, -1));
    primero.push_back(punto2D<float>(1, -1));

    cola.push_back(new poligono2D<float>(primero));

    for(int i=0; i<iterations; i++){
        poligono2D<float>* actual = cola.front();
        cola.pop_front();

        poligono2D<float>* resta = subtriangulo(actual);
        vector<segmento2D<float> >* segmentos = diferenciaPoligonos(actual, resta);
        vector<poligono2D<float> >* nuevos = reconstruye(segmentos);
        ps = diferencia(e, kk);
    }
}
