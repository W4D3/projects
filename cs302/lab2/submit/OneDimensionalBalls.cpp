#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <vector>
#include <map>

using namespace std;

// OneDimensionalBalls.cpp
// Mitchell Wade
// Sep. 14, 2014
//
// This program counts the number of valid guesses that the balls can travel in space.
// Using maps, a set, and pointers the program is able to keep track of the valid 
// velocities that each ball can travel and then we traverse the maps using pointers to
// count the number of valid guesses that are possible for the set of velocities.

class Ball {
    public:
        int val;
        Ball *low;
        Ball *high;
        bool removed; // Keeps track of the connections between balls
};

class OneDimensionalBalls {
    public:
        long long countValidGuesses(vector <int> firstPicture, vector <int> secondPicture);
        long long cvg(int v);
        map<int, Ball *> FP;
        map<int, Ball *>::iterator fit;
        map<int, Ball *> SP;
        map<int, Ball *>::iterator sit;
};

long long OneDimensionalBalls::cvg(int v) {

    int rv = 0, flag, count = 0;
    Ball *b;

    // Reset pointers
    for (fit = FP.begin(); fit != FP.end(); fit++) {
        fit->second->high = NULL;
        fit->second->low = NULL;
        fit->second->removed = false;
    }
    
    for (fit = SP.begin(); fit != SP.end(); fit++) {
        fit->second->high = NULL;
        fit->second->low = NULL;
        fit->second->removed = false;
    }


    // Set the pointers of each ball in both maps
    for (fit = FP.begin(); fit != FP.end(); fit++) {

        b = fit->second; // Grab the ball

        // Search for the next ball that could connect as high
        sit = SP.find(b->val-v);
        if (sit != SP.end()) { // If found, set the pointers
            b->low = sit->second;
            sit->second->high = b;
        } else {
            b->low = NULL; 
        }

        // Search for the next ball that cound connect as low
        sit = SP.find(b->val+v);
        if (sit != SP.end()) { // If found, set the pointers
            b->high = sit->second;
            sit->second->low = b;
        } else {
            b->high = NULL; 
        }
    }


    // Count the number of valid guesses
    do {
        flag = 0;

        for (fit = FP.begin(); fit != FP.end(); fit++) {

            b = fit->second; // Grab the ball

            //fflush(stdout);

            // If it has already been removed skip to the next ball
            // This continues through the while loop to the next iteration
            if (b->removed == true) {
                continue;
            }

            // Return 0 valid guesses if a ball can't be matched to another position
            if ((b->high == NULL) && (b->low == NULL)) {
                return 0;
            }

            // Set the ball as removed if it only has one possible spot to move too
            if ((b->high == NULL) && (b->low != NULL)) {

                // Set the ball as removed
                b->removed = true;

                // Unlink the next ball
                if (b->low->low != NULL) {
                    
                    b->low->low->high = NULL;
                }

                // Exits the while loop
                flag = 1;
            }

            // Set the ball as removed if it only has one possible spot to move too
            if ((b->low == NULL) && (b->high != NULL)) {

                // Set the ball as removed
                b->removed = true;

                // Unlink the next ball
                if (b->high->high != NULL) {

                    b->high->high->low = NULL;
                }

                // Exits the while loop
                flag = 1;
            }
        }

    } while (flag == 1);

    // Set the count to two because we know we must have at least two guesses,
    // and then iterate through the map and add the number of guesses to count 
    rv = 1;
    for (fit = FP.begin(); fit != FP.end(); fit++) {
        
        // Grab the next ball
        b = fit->second;

        // Count valid guesses
        if (b->removed == false) {
            count = 2;
            while (b->high->high != NULL) {
                count++;
                b->removed = true; // Set it as removed because it has been counted
                b = b->high->high; // Go to the next ball
            }

            // Multiply the number of guesses
            b->removed = true;
            rv *= count;

        }
    }

    return rv;
}

long long OneDimensionalBalls::countValidGuesses(vector <int> firstPicture, vector <int> secondPicture) {

    int i = 0, v = 0, sum = 0;
    Ball *b;
    set <int> velocities;
    set <int>::iterator vit;

    // Adds the contents of firstPicture to the FP map
    for (i = 0; i < firstPicture.size(); i++) {
        b = new Ball;
        b->val = firstPicture[i];
        FP[firstPicture[i]] = b;
        FP.insert(make_pair(b->val, b));
    }

    // Adds the contents of secondPicture to the SP map
    for (i = 0; i < secondPicture.size(); i++) {
        b = new Ball;
        b->val = secondPicture[i];
        SP[secondPicture[i]] = b;
        SP.insert(make_pair(b->val, b));
    }

    // Calculates all of the velocites
    for (i = 0; i < secondPicture.size(); i++) {
        v = secondPicture[i] - firstPicture[0];
        if (v < 0) v = -v;
        if (v != 0) velocities.insert(v);
    }

    // Counts the number of valid guesses
    for (vit = velocities.begin(); vit != velocities.end(); vit++) {
        long long tmp = cvg(*vit);
        sum += tmp;
    }

    return sum;
}
