#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

typedef vector <int> IVec;

/*
   neg.cpp
   Mitchell Wade
   February 6, 2014

   This program takes a PGM file on standard input, and prints a PGM file
   on standard output that is negative of the input file. If the PGM file
   is not valid (same parameters as pgminfo), print an error to stderr.
*/

int main(){
    
    /* Variables */
    int i, j, r, c, p, n;
    int neg = 0;
    string s;
    vector <IVec> pgm;
    
    /* Read in the values and check the file for errors */
    if (!(cin >> s) || s != "P2"){
        cerr << "Bad PGM file -- first word is not P2\n";
        exit(0);
    }
    
    if (!(cin >> c) || c <= 0){
        cerr << "Bad PGM file -- No column specification\n";
        exit(0);
    }
    
    if (!(cin >> r) || r <= 0){
        cerr << "Bad PGM file -- No row specification\n";
        exit(0);
    }
    
    if (!(cin >> n) || n != 255){
        cerr << "Bad PGM file -- No 255 following the rows and columns\n";
        exit(0);
    }
    
    /* Calculates the number of pixels and declare memory */
    p = c*r;
    pgm.resize(p);
    
    /* Read through each pixel */
    for (i=0; i<p; i++){
        cin >> n;

        if (n < 0 || n > 255){
            cerr << "Bad PGM file -- pixel " << i << " is not a number between 0 and 255\n";
            exit(0);
        }

        /* Calculates the negative PGM values */
        neg = (255-n);
        pgm[i].push_back(neg);

    }
    
    if (cin >> s){
       cerr << "Bad PGM file -- Extra stuff after the pixels\n";
        exit(0);
    }

    /* Print the negative PGM file specifications */
    printf("P2\n%3d %3d\n255\n", c, r);
    
    /* Print the negative pixels */
    for (i = 0; i < pgm.size(); i++){
        for (j = 0; j < pgm[i].size(); j++) printf(" %1d", pgm[i][j]);
        cout << endl;
    }
}
