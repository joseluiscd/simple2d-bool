#include "math.h"

double dotProduct(double x1, double y1, double x2, double y2){
    return x1*x2 + y1*y2;
}

double dotProduct(const point2d &point1, const point2d &point2){
    return dotProduct(point1.x, point1.x, point2.x, point2.y);
}

double determinant(double a, double b, double c, double d){
	return (a*d - b*c);
}
