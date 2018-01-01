#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

typedef vector <double> DVec;

/* dond.cpp
   Mitchell Wade
   December 1, 2014

   This program calculates the probability of rolling a s-sided dice
   t times until your last roll, lr. It uses dynamic programming to 
   memoize a recursive solution. By adding in a cache to store the 
   probablity of each possible roll of the dice we are able to exp.
   increase the program speed to get a solution.
*/

class dond {
    public:
        double Calc(double s, double t, double lr);
        vector <DVec> cache;
};

// Calculates the probability
double dond::Calc(double s, double t, double lr) {

    int i;
    double sum = 0;

    // Resize the cache vector and initialize all elements to -1
    if (cache.size() == 0) {
        cache.resize(t+1);
        for (i = 0; i < cache.size(); i++) cache[i].resize(s+1, -1);
    }

    // Return that element if it has already been computed
    if (cache[t][lr] != -1) return cache[t][lr];

    // Return if there are no more rolls
    if (t == 0) return 1;

    // Add up the probability
    for (i = 0; i < s; i++) {
        if (lr == s || abs(lr-i) > 1) {
            sum += Calc(s, t-1, i);
        }
    }

    // Set the cache value and return
    if (cache[t][lr] == -1) return cache[t][lr] = sum/s;
}

int main(int argc, char** argv)
{
    dond d;
    int i, j, s, t, lr;

    // Read in values for the cmd line
    s = atoi(argv[1]);
    t = atoi(argv[2]);
    lr = atoi(argv[3]);

    // Special case for indexing into the lr element
    if(lr == -1) lr = s;

    // Print out the probability
    cout << d.Calc(s, t, lr) << endl;

	return 0;
}
