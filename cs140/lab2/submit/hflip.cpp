#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
   hflip.cpp
   Mitchell Wade
   February 6, 2014
   
   This program takes a PGM file on standard input, and prints a PGM file
   on standard output that is flipped horizontally.
*/

typedef vector <int> IVec;

int main(){
    /* Variables */
    int i, j, r, c, p, n;
    string s, temp;
    vector <IVec> pgm;

    /* Read in the values and  check the input for errors/correct usage */
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

    /* Calculates the total number of pixels */
    p = c*r;

    /* Declare a properally allocated vector for data/memory */
    pgm.resize(r);
    
    /* Read through each pixel and check input for errors */
    for (i=0; i<pgm.size(); i++){
        for(j=0; j<pgm.size(); j++){
            if(cin >> n){
                
                pgm[i].push_back(n);

                if (n < 0 || n > 255){
                    cerr << "Bad PGM file -- pixel " << i  
                        << " is not a number between 0 and 255\n";
                    exit(0);
                }
            }

    if (cin >> s){
        cerr << "Bad PGM file -- Extra stuff after the pixels\n";
        exit(0);
    }

    /* Print the PGM file specifications */
    printf("P2\n%3d %3d\n255\n", c, r);
    
    /* Print the pixels*/
    for (i = 0; i < pgm.size(); i++){
        for (j = pgm[i].size(); j >= 0; j--) printf(" %1d", pgm[i][j]);
        cout << endl;
    }
        }
    }
}
