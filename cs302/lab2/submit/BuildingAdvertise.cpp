#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

// BuildingAdvertise.cpp
// Mitchell Wade
// Sep. 14, 2014
// 
// This program determines the largest amount of advertising space that can
// be found on a skyline. The skyline is represented by a vector of heights
// whose position is modeled by the variable n in the skyline. The prog.
// copies the contents of R which holds the skyline into a map so that we
// can use an iterator to search the map. Then the prog. adds the sentinels
// to a set and searches the map for the upperbound which is the maximum 
// distance the advertisement can be placed into. Next the prog. uses the
// upperbound to find the lower bound which is done by decrementing the 
// iterator. Then we use a simple area formula to find the area between the
// lower and upper bound which is the total size of the advertisement and
// return that value.

class BuildingAdvertise {
    public:
        long long getMaxArea(vector <int> h, int n);
};

long long BuildingAdvertise::getMaxArea(vector <int> h, int n) {

    vector <long long> R;
    long long i = 0, j = 0, s = 0, m = 0, area = 0, r = 0, l = 0, rv = 0;
    multimap <long long, long long> MM;
    multimap <long long, long long>::iterator mit;
    set <long long> X;
    set <long long>::iterator xit;


    // Transform the skyline
    m = h.size();
    R.resize(n);
    for (i=0; i<n; i++) {
        R[i] = h[j];
        s = (j+1)%m;
        h[j] = ( ( h[j] ^ h[s] ) + 13 ) % 835454957;
        j = s;
    }

    // Create the sentinels
    R.push_back(0);
    R.insert(R.begin(), 0);

    // Put the contents of R into the multimap
    for (i=0; i<R.size(); i++) {
        MM.insert(make_pair(R[i], i));
    }

    // Look for upper and lower bounds and calculate the area
    for (mit = MM.begin(); mit != MM.end(); mit++) {
        if (mit->first == 0) { // If it is a sentinel add the indice to the set
            X.insert(mit->second);
        } else {
            xit = X.upper_bound(mit->second); // Find the upper bound
            r = *xit; // Grab the upper bound indice
            xit--;
            l = *xit; // Grab the lower bound indice
            area = mit->first * (r-l-1);
            if (area > rv) rv = area;
            X.insert(mit->second);
        }
    }

    return rv;
}
