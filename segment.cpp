#include "segment.h"
#include "triangle.h"

bool pointInSegment(const point2d& point, const segment2d& segment, int precision){
	double v1x, v1y;
	double v2x, v2y;

    if(sign(doubleSignedArea(segment, point), precision)==0){
		v1x = point.x - segment.a.x;
		v1y = point.y - segment.a.y;
		v2x = point.x - segment.b.x;
		v2y = point.y - segment.b.y;

		//If sign == 0 -> the point is one of the segment's end points
		//If sign == -1 -> the point is inside the segment
        return sign(dotProduct(v1x, v1y, v2x, v2y)) <= 0;
    }
	return false;
}

segmentRelSegment segmentRelativeToSegment(const segment2d& first, const segment2d& second, int precision){
	int x11 = sign(first.a.x, second.a.x, precision);
	int x12 = sign(first.a.x, second.b.x, precision);
	int x21 = sign(first.b.x, second.a.x, precision);
	int x22 = sign(first.b.x, second.b.x, precision);

	int y11 = sign(first.a.y, second.a.y, precision);
	int y12 = sign(first.a.y, second.b.y, precision);
	int y21 = sign(first.b.y, second.a.y, precision);
	int y22 = sign(first.b.y, second.b.y, precision);

	if( !(x11 && x12 && x21 && x22) && !(y11 && y12 && y21 && y22) ){
		//Some X and Y are the same. They are connected or the same segment.
		if(sign(doubleSignedArea(first, second.a), precision)
			|| sign(doubleSignedArea(first, second.b), precision))
			{
				return CONNECTED;
		}
		return EQUALS;
	} else if(
		sign(doubleSignedArea(first, second.a))==-sign(doubleSignedArea(first, second.b))
		&&
		sign(doubleSignedArea(second, first.a))==-sign(doubleSignedArea(second, first.b)))
		{
			return INTERSECT;
	} else if(pointInSegment(first.a, second) || pointInSegment(first.b, second)
		|| pointInSegment(second.a, first) || pointInSegment(second.b, first))
		{
			//Check if there is a "T" intersection
			return INTERSECT;
	} else {
		return NO_RELATION;
	}
}


point2d middlePoint(const segment2d& s){
	return middlePoint(s.a, s.b);
}


double cosAngle(const segment2d& first, const segment2d& second){
	return ((first.b.x-first.a.x) * (second.b.x-second.a.x) + (first.b.y-first.a.y) * (second.b.y-second.a.y))/(distance(first.a, first.b)*distance(second.a, second.b));
}


int orientation(const segment2d& first, const segment2d& second, int precision){
	return sign(determinant(first.b.x-first.a.x, first.b.y-first.a.y, second.b.x-second.a.x, second.b.y-second.a.y), precision);
}

point2d intersectionPoint(const segment2d& first, const segment2d& second, int precision){
	point2d toRet;

	double a1 = first.b.y - first.a.y;
	double a2 = - first.b.x + first.a.x;
	double a3 = second.b.y - second.a.y;
	double a4 = - second.b.x + second.a.x;

	double denom = determinant(a1,a2,a3,a4);

	if (sign(denom, precision)==0){
		throw parallelSegments(); // They are parallel
	}

	//Compute X
	a1 = first.a.x*(first.b.y-first.a.y) - first.a.y*(first.b.x-first.a.x);
	a3 = second.a.x*(second.b.y-second.a.y) - second.a.y*(second.b.x-second.a.x);

	toRet.x = determinant(a1,a2,a3,a4) / denom;

	//Compute Y
	a1 = first.b.y - first.a.y;
	a2 = first.a.x*(first.b.y-first.a.y) - first.a.y*(first.b.x-first.a.x);
	a3 = second.b.y - second.a.y;
	a4 = second.a.x*(second.b.y-second.a.y) - second.a.y*(second.b.x-second.a.x);

	toRet.y = determinant(a1,a2,a3,a4) / denom;

	return toRet;
}


segment2d inverseSegment(const segment2d& s){
	return segment2d(s.b, s.a);
}
