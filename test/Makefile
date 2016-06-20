TESTS = intersection.out diferencia.out union.out generapoligono.out

test: $(TESTS)

%.out: %.cpp ../libalgoritmos.so
	g++ -g -std=c++11 -I.. -L.. -lalgoritmos $< -o $@
