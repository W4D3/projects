#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

typedef vector <int> IVec;

/*
   bigwhite.cpp
   Mitchell Wade
   February 6, 2014
 
   This program takes two command line arguements as input and uses those values,
   if they are integers, as the values for rows and columns in the pgm file. It
   then outputs a pgm file to standard output which is equivilent to the every
   pixel represented as a white pixel (255).

*/


int main(int argc, char **argv)
{
    /* Variables */
    int i, j, r, c;
    istringstream ss;
    vector <IVec> pgm;
    int pixel;

    /* Initalize each pixel to white */
    pixel = 255;
    
    /* Print stderr if usage is inccorect */
    if (argc !=3 ){ 
        fprintf(stderr, "usage: bigwhite rows cols\n");
        return 1;
        }

    /* Read in the rows */
    ss.clear();
    ss.str(argv[1]);
    if (!(ss >> r) || r <= 0 ){
        fprintf(stderr, "usage: bigwhite rows cols\n");
        return 1;
        }
    
    /* Read in the columns */
    ss.clear();
    ss.str(argv[2]);
    if (!(ss >> c) || c <= 0){
        fprintf(stderr, "usage: bigwhite rows cols\n");
        return 1;
        }

    /* Print the standard PGM file specifications */
    printf("P2\n%3d%3d\n255\n", c, r);

    /* Print the white pixels */
    pgm.resize(r);
      for (i = 0; i < pgm.size(); i++){
          for (j = 0; j < c; j++){
              pgm[i].push_back(pixel);
          }
      }
      
      for (i = 0; i < pgm.size(); i++){ 
          for (j = 0; j < pgm[i].size(); j++) printf(" %1d", pgm[i][j]);
          cout << endl;
      }
}
