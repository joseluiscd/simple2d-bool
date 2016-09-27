#include "signo.h"

int signo(int a){
	if(a > 0){
		return 1;
	} else if (a < 0){
		return -1;
	} else {
		return 0;
	}
}

inline int signo(double a, double b, int precision){
	return signo(a-b, precision);
}

int signo(double a, int precision){
	long p = std::pow(10, -precision);

	if(a > p){
		return 1;
	} else if (a < p){
		return -1;
	} else {
		return 0;
	}
}
