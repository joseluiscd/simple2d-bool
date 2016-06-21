TESTS = intersection.out diferencia.out union.out generapoligono.out union_file.out interseccion_file.out diferencia_file.out triangulo.out

test: $(TESTS)

%.out: %.cpp ../libalgoritmos.so
	g++ -g -std=c++11 -I.. -L.. -lalgoritmos $< -o $@
