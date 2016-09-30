#ifndef _SIGN_H
#define _SIGN_H

#include <cmath>

int signo(double a, double b, int precision=3);
int signo(double a, int precision=3);
int signo(int a);

/*TODO: Decidir si aquí va alguna variable global para evitar pasar la precisión
a todas las funciones (igual que en point.h con la variable estática de clase)

Al final todas las variables precisión van a las funciones signo.
*/

#endif
