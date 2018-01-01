#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "sorting.h"

using namespace std;

void recursive_sort(vector <double> &v, int start, int size, int print) {

    int i, iLeft, iRight;
    double pivot;
    double first = v[start];
    double last = v[start+size-1];
    double middle = v[start+size/2];
    double median, tmp;
    
    // Base case
    if (size == 1) return;


    // Print out the vector
    if (print) {
        printf("S: %5d %5d %5s", start, size, "");
        if (size > 1) {
            for (i = 0; i < v.size(); i++) {
                printf("%5.2lf", v[i]);
            }
            printf("\n");
        }
    }

    // Base case
    if (size == 2) {
        if (v[start] > v[start+1]) {
            tmp = v[start];
            v[start] = v[start+1];
            v[start+1] = tmp;
        }
        return;
    }

    // Find the median of the first, middle, and last 
    // element of the vector
    if ((first < last) && (first > middle)) median = first;
    else if ((middle < last) && (middle > first)) median = middle;
    else if ((first > last) && (first < middle)) median = first;
    else if ((middle > last) && (middle < first)) median = middle;
    else if ((first < last) && (last < middle)) median = last;
    else median = last;

    // Set the pivot
    pivot = median;

    // Swap the median to the first spot in the vector
    if (v[start] != median) {
        if (median == v[start+size-1]) {
            tmp = v[start];
            v[start] = v[start+size-1];
            v[start+size-1] = tmp;
        } else if (median == v[start+size/2]) {
            tmp = v[start];
            v[start] = v[start+size/2];
            v[start+size/2] = tmp;
        }
    }

    // Set the indicies
    iLeft = start+1;
    iRight = start+size-1;

    // Print out the vector
    if (print) {
        printf("M: %5d %5d %5.2lf", start, size, pivot);
        if (size > 1) {
            for (i = 0; i < v.size(); i++) {
                printf("%5.2lf", v[i]);
            }
            printf("\n");
        }
    }


    // Quicksort swapping
    //for (i = start; i < start+size; i++) {
    while (iLeft <= iRight) {
        while (v[iLeft] <= pivot) iLeft++;
        while (v[iRight] >= pivot) iRight--;
            if (iLeft <= iRight) {
                tmp = v[iLeft];
                v[iLeft] = v[iRight];
                v[iRight] = tmp;
                iLeft++;
                iRight--;
            }
    }

    // Swap the pivot with iLeft-1
    tmp = v[start];
    v[start] = v[iLeft-1];
    v[iLeft-1] = tmp;

    // Print out the vector
    if (print) {
        printf("P: %5d %5d %5d", start, size, iLeft-1);
        if (size > 1) {
            for (i = 0; i < v.size(); i++) {
                printf("%5.2lf", v[i]);
            }
            printf("\n");
        }
    }

    // Recursive calls on each half of the vector
    recursive_sort(v, start, iLeft-1-start, print);
    recursive_sort(v, iLeft, start+size-iLeft, print);
}

void sort_doubles(vector <double> &v, int print) {

    // Quicksort
    recursive_sort(v, 0, v.size(), print);

    // Print out the final vector
    printf("                ");
    for (int i = 0; i < v.size(); i++) {
        printf("%5.2lf", v[i]);
    }
    printf("\n");
}
