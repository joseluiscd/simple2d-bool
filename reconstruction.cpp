#include "reconstruction.h"

using namespace std;

//Inefficient version of the algorithm TODO: Use hashtable
vector<polygon2d* >* rebuildPolygonsFromSegments(const vector<segment2d >& segmentos, int precision){
    vector<polygon2d* >* ret = new vector<polygon2d* >();
    list<segment2d > rest(segmentos.begin(), segmentos.end());

    //Remove elements that are points
    for(auto it=rest.begin(); it!=rest.end(); it++){
        if(it->b == it->a){
            //It's a point
            it = prev(rest.erase(it));
        }
    }

    while(!rest.empty()){
        list<point2d > points;
        segment2d current = rest.front();
        segment2d first = current;

        rest.pop_front();

        points.push_back(current.a);
        bool stop=false;
        while(!stop){
            auto candidate = rest.end();
            double coseno = -1;
            for(auto it=rest.begin(); it!=rest.end(); it++){
                if(sign(squaredDistance(current.b, it->a), precision)==0){
                    if(candidate==rest.end()){
                        candidate = it;
                    } else {
                    	//Check angle
                    	double c = cosAngle(inverseSegment(current), *it);
                        int o = orientation(inverseSegment(current), *it);
                        if((o==-1 || o==0) && c>coseno){
                            candidate = it;
                            coseno = c;
                        }
                    }

                }
            }

            //Add the new segment to our polygon
            points.push_back(candidate->a);
            current = *candidate;

            if(sign(squaredDistance(current.b, first.a), precision)==0){
                stop = true;
                ret->push_back(new polygon2d(points));

                points.clear();
            }

            rest.erase(candidate);

        }

    }

    return ret;
}
