OBJECTS = main.o signo.o loader_poligono.o random_poligono.o
HEADERS = poligono.h punto.h segmento.h triangulo.h signo.h bool_poligono.h

.PHONY: test

all: main

test: libalgoritmos.so
	$(MAKE) -C ./test test

libalgoritmos.so: $(OBJECTS) $(HEADERS)
	g++ -g -std=c++11 -shared $(OBJECTS) -fPIC -o $@

main: $(OBJECTS) $(HEADERS)
	g++ -g -std=c++11 $(OBJECTS) -o $@

%.o: %.cpp $(HEADERS)
	g++ -g -fPIC -std=c++11 -c $< -o $@
