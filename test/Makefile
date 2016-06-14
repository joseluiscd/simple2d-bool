TESTS = intersection.exe

test: $(TESTS)

%.exe: %.cpp
	g++ -std=c++11 -I.. -L.. -l algoritmos $< -o $@
