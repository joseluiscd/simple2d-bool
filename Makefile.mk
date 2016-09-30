OBJECTS = math.o point.o segment.o triangle.o polygon.o bool_polygon.o loader_polygon.o random_polygon.o dump_polygon.o reconstruction.o
HEADERS = math.h point.h segment.h triangle.h polygon.h bool_polygon.h loader_polygon.h random_polygon.h dump_polygon.h reconstruction.h
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
