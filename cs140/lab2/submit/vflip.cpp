#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

typedef vector <int> IVec;

/*
   vflip.cpp
   Mitchell Wade
   February 4, 2014
   
   This program takes a PGM file on standard input, and prints a PGM file
   on standard output that is flipped horizontally.
*/

vector <int> reverse(vector <int> v)
{
    vector <int> rv;
    int i;
    
    for (i = v.size()-1; i >= 0; i--) rv.push_back(v[i]);
    return rv;
}

int main(){
    
    /* Variables */
    int i, j, r, c, p, n;
    int horizontal = 0;
    string s;
    vector <IVec> pgm;

    /* Check the file for errors */
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
        cerr << "Bad PGM file -- Number following pixels doesn't equal 255\n";
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
        
    /* Calculates the horizontally flipped PGM values */
       reverse(pgm[i]);
    }
    
    //if (!cin.eof()){
    //    cerr << "Bad PGM file -- Extra stuff after the pixels\n";
    //    exit(0);
    //}
    
    /* Print the negative PGM file specifications */
    printf("P2\n%3d %3d\n255\n", c, r);
    
    /* Print the negative pixels */
    for (i = 0; i < pgm.size(); i++) {
        for (j = 0; j < pgm[i].size(); j++) printf(" %1d", pgm[i][j]);
        cout << endl;
    }
}


