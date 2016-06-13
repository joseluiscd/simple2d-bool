#include "signo.hpp"

int signo(int a){
	return 	a>0 ? 1 :
			a<0 ? -1 :
			0;
}
