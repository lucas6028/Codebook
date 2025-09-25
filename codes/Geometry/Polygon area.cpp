/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Status: Stress-tested and tested on kattis:polygonarea
 */
#pragma once

#include "Point.h"

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

int main() {
    // Example: square with vertices (0,0), (0,1), (1,1), (1,0)
    vector<Point<long long>> poly = {
        {0,0}, {0,1}, {1,1}, {1,0}
    };

    long long area2 = polygonArea2(poly);
    cout << "Twice signed area = " << area2 << "\n";
    cout << "Absolute area = " << abs(area2) / 2.0 << "\n";

    return 0;
}