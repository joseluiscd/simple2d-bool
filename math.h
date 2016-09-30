#ifndef _MYMATH_H
#define _MYMATH_H

#include <cmath>

int sign(double a, double b, int precision=3);
int sign(double a, int precision=3);
int sign(int a);
double dotProduct(double x1, double y1, double x2, double y2);
double determinant(double a, double b, double c, double d);

#endif
