#include <assert.h>
#include <vector>
#include "polygon.h"

#define CHECK(p, t, r) (assert(pointInPolygon(p, t)==r))

int main(int argc, char* argv[]){
    std::vector<point2d> vert1 {
        {0,0}, {2,0}, {2,2}, {1,1}, {0,1}
    };

    std::vector<point2d> vert2 {
        {0,0}, {1,0}, {1,1}, {0,1}
    };

    polygon2d pol1(vert1);
    polygon2d pol2(vert2);

    point2d point1 {0.5, 0.5};
    point2d point2 {0,0};
    point2d point3 {0.5, 1};

    CHECK(point1, pol1, INSIDE_POSITIVE);
    CHECK(point1, pol2, INSIDE_POSITIVE);

    //Bounding box check
    CHECK(point2, pol1, BORDER);
    CHECK(point2, pol2, BORDER);

    //Border check (no bounding box)
    CHECK(point3, pol1, BORDER);
    return 0;
}
