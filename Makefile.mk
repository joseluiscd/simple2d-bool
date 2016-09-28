OBJECTS = math.o signo.o point.o segment.o triangle.o polygon.o loader_polygon.o random_polygon.o
HEADERS = math.h signo.h point.h segment.h triangle.h polygon.h loader_polygon.h random_polygon.h
MAIN = main.o

.PHONY: test

all: main

test: libalgoritmos.so
	$(MAKE) -C ./test test

libalgoritmos.so: $(OBJECTS) $(HEADERS)
	g++ -g -std=c++11 -shared $(OBJECTS) -fPIC -o $@

main: $(OBJECTS) $(MAIN) $(HEADERS)
	g++ -g -std=c++11 $(OBJECTS) $(MAIN) -o $@

%.o: %.cpp $(HEADERS)
	g++ -g -fPIC -std=c++11 -c $< -o $@
