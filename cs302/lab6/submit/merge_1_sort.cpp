#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "sorting.h"

using namespace std;

/*
   merge_1_sort.cpp
   Mitchell Wade
   October 24, 2014

   This program sorts an input vector using merge sort.
 */

void recursive_sort(vector <double> &v, vector <double> &temp, int start, int size, int print) {

    int i, iLeft, iRight;

    // Base case
    if (size == 1) return;

    if (print) {
        // Print out the vector
        printf("B: %5d %5d  ", start, size);
        if (size > 1) {
            for (i = 0; i < v.size(); i++) {
                printf("%5.2lf", v[i]);
            }
            printf("\n");
        }
    }

    // Break the vector into two halves continously 
    // until it hits the base case
    recursive_sort(v, temp, start, size/2, print);
    recursive_sort(v, temp, start + size/2, size-size/2, print);

    // Set the indices
    iLeft = start;
    iRight = start+size/2;

    // Creates the sorted vector
    for (i = start; i < start+size; i++) {

        // Pick the smallest element, and add it
        // to the temp. vector
        if (iLeft == start+size/2) {
            temp[i] = v[iRight];
            iRight++;
        } else if (iRight == start+size) {
            temp[i] = v[iLeft];
            iLeft++;
        } else if (v[iLeft] < v[iRight]) {
            temp[i] = v[iLeft];
            iLeft++;
        } else {
            temp[i] = v[iRight];
            iRight++;
        }
    }
    
    // Copy the vector
    v = temp;

    // Print out the vector
    if (print) { 
        printf("E: %5d %5d  ", start, size);
        if (size > 1) {
            for (i = 0; i < v.size(); i++) {
                printf("%5.2lf", v[i]);
            }
            printf("\n");
        }
    }
}

void sort_doubles(vector <double> &v, int print) {

    vector <double> tmp(v);

    // Mergesort
    recursive_sort(v, tmp, 0, v.size(), print);

    // Print out the final vector
    printf("                ");
    for (int i = 0; i < v.size(); i++) {
        printf("%5.2lf", v[i]);
    }
    printf("\n");
}
