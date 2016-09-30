#include "math.h"

double dotProduct(double x1, double y1, double x2, double y2){
    return x1*x2 + y1*y2;
}

double determinant(double a, double b, double c, double d){
	return (a*d - b*c);
}

int sign(int a){
	if(a > 0){
		return 1;
	} else if (a < 0){
		return -1;
	} else {
		return 0;
	}
}

int sign(double a, double b, int precision){
	return sign(a-b, precision);
}

int sign(double a, int precision){
	long p = std::pow(10, -precision);

	if(a > p){
		return 1;
	} else if (a < p){
		return -1;
	} else {
		return 0;
	}
}
