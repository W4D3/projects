#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
   pgminfo.cpp
   Mitchell Wade
   February 6, 2014
 
   This program outputs investigates a pgm file when the file is read
   through standard input. It then calculates the average number of
   pixels and the total pixels which is output to standard output
   along with the number of rows and columns the pgm file consists of. 
 
 */



int main()
{
    /* Variables */
    int i, r, c, n;
    double p, avgPix;
    double totalPix = 0;
    string s;
    
    /* Check the file for errors */
    if (!(cin >> s) || s != "P2"){
        cerr << "Bad PGM file -- first word is not P2\n"; 
        exit(0);
    }
    
    if (!(cin >> c) || (c <= 0)){ 
        cerr << "Bad PGM file -- No column specification\n";
        exit(0);
    }
    if (!(cin >> r) || (r <= 0)){
        cerr << "Bad PGM file -- No row specification\n";
        exit(0);
    }
    if (!(cin >> n) || (n != 255)){
        cerr << "Bad PGM file -- Number following pixels doesn't equal 255\n";
        exit(0);
    }

    /* Calculates the number of pixels */
    p = c*r;

    /* Averages the pixels */
    for (i=0; i<p; i++){
        cin >> n;
        if (n < 0 || n > 255){
            cerr << "Bad PGM file -- pixel " << i << 
                " is not a number between 0 and 255\n";
            exit(0);
        } else {totalPix+=n;}
    }
    
    if (cin >> s){
          cerr << "Bad PGM file -- Extra stuff after the pixels\n";
         exit(0);
    }

    /* Calculate the average number of pixels */
    avgPix = totalPix/p;
    
    printf("# Rows:     %7.0d\n", r);
    printf("# Columns:  %7.0d\n", c);
    printf("# Pixels:   %7.0lf\n", p);
    printf("Avg Pixel:  %7.3lf\n", avgPix);
    exit(0);
}
