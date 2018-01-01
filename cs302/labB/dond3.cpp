#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

/*
   dond.cpp
   Mitchell Wade
   November 25, 2014

*/

//typedef vector <int> IVec;

int main(int argc, char **argv) {

    int i, j, s, t, lr, tmp, tmp2, prob, prob2, count;
    vector <int> P, P2;

    // Check for proper usage
    if (argc != 4) {
        cerr << "usage: dond s t last-roll\n";
        exit(1);
    }

    // Read in values
    s = atoi(argv[1]);
    t = atoi(argv[2]);
    lr = atoi(argv[3]);

    // Initialize the probability vectors to the proper size
    P.resize(s, 1);
    P2.resize(s, 1);

    count = 0;
    while (count != t) {

        // Clear the tmp variables
        tmp = 0;
        tmp2 = 0;

        // Calculate the probability
        for (i = 0; i < P.size()-1; i++) {
            if (i != P[lr] || i != P[lr-1] || i != P[lr+1]) {
                tmp += P[i];
            } else if (i == P[lr] || i == P[lr-1] || i == P[lr+1]) {
                tmp2 += P[i];
            }
        }

        // Change each elements probability
        for (i = 0; i < P.size()-1; i++) {
            if (i != P[lr] || i != P[lr-1] || i != P[lr+1]) {
                P[i] = tmp/s;
            } else if (i == P[lr] || i == P[lr-1] || i == P[lr+1]) {
                P[i] = tmp2/s;
            }
        }
    }

    return P[lr];
}

/*
   for (i = 0; i < P.size()-1; i++) {
   if (i == 0 || i == P.size()-1) {
//p[i] = s-2/s;
tmp += P[i];
}
else if (i != 0 || i != P.size()-1 || i != P.size()) {
//p[i] = s-3/s;
tmp2 += P[i];
}
}

prob = (1/s)*tmp;
prob2 = (1/s)*tmp2;
}
 */
/*
   void changeP (int s, int t, int lr, vector <int> p) {

   int i, probB, probG, probT;

   while (t != 0) {
// Add up the prob. for each position
for (i = 0; i < p.size()-1; i++) {
if (i == lr || i == lr-1 || i == lr+1) probB += p[i];
else if (i != lr || i != lr-1 || i != lr+1) probG += p[i];
probT += p[i];
}

// Change the prob. in the vector
p[p.size()] = probT;
for (i = 0; i < p.size()-1; i++) {
if (i == lr || i == lr-1 || i == lr+1) p[i] = probG;
else if (i != lr || i != lr-1 || i != lr+1) p[i] = probB;
}

t--;
}
}
 */
/*
// Calculate the first rolls prob.
for (i = 0; i < p.size()-1; i++) {
if (i == 0 || i == p.size()-1) p[i] = s-2/s;
else if (i != 0 || i != p.size()-1 || i != p.size()) p[i] = s-3/s;
}

// Solve for the probability
changeP(s, t, lr, p);

// Return the probability
return p[lr];
 */