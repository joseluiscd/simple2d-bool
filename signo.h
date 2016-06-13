#include <cmath>

#ifndef _SIGNO_H
#define _SIGNO_H

template<typename T>
int signo(T a, T b, int precision=3){
	a = a-b;
	long p = pow(10, -precision);

	return 	a > p ? 1 :
			a < p ? -1 :
			0;
}

template<typename T>
int signo(T a, int precision=3){
	long p = pow(10, -precision);

	return 	a > p ? 1 :
			a < p ? -1 :
			0;
}

int signo(int a);
#endif
