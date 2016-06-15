TESTS = intersection.exe

test: ../algoritmos.dll $(TESTS)

%.exe: %.cpp ../algoritmos.dll
	g++ -g -std=c++11 -I.. -L.. -l algoritmos $< -o $@
