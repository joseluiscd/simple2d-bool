OBJECTS = main.o signo.o loader_poligono.o
HEADERS = poligono.hpp punto.hpp segmento.hpp triangulo.hpp signo.hpp
all: main

main: $(OBJECTS) $(HEADERS)
	g++ -g -std=c++11 $(OBJECTS) -o $@
	
%.o: %.cpp $(HEADERS)
	g++ -g -std=c++11 -c $< -o $@

