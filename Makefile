OBJECTS = main.o signo.o loader_poligono.o
HEADERS = poligono.h punto.h segmento.h triangulo.h signo.h
all: main

main: $(OBJECTS) $(HEADERS)
	g++ -g -std=c++11 $(OBJECTS) -o $@

%.o: %.cpp $(HEADERS)
	g++ -g -std=c++11 -c $< -o $@
