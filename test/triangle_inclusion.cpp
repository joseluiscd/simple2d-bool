#include <assert.h>
#include <point.h>
#include "triangle.h"

#define CHECK(p, t, r) (assert(pointInTriangle(p, t)==r))

int main(){
    point2d p1(0,0);
    point2d p2(1,0);
    point2d p3(0,1);
    point2d p4(0, 0.5);

    triangle2d t1(p1, p2, p3);

    CHECK(p1, t1, BORDER);
    CHECK(p2, t1, BORDER);
    CHECK(p4, t1, BORDER);


}
