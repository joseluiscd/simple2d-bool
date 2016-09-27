OBJECTS = main.o signo.o point.o segment.o loader_poligono.o random_poligono.o triangle.o
HEADERS = poligono.h point.h segment.h triangle.h signo.h bool_poligono.h reconstruccion.h

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
