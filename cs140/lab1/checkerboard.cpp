#include <iostream> 
#include <cstdlib> 
#include <cstdio> 
#include <string>

/* checkerboard.cpp
   Mitchell Wade
   January 31, 2014
   
   This program uses 4 four loops and the formula, SC+(R+C)%CS, to get the proper output
   of grouped numbers and characters similar to a checkerboard.
 
 */

using namespace std;

//use SC+(r+c)%CS

int main(){

        int i, j, x, z; /* Iteration Variables */
        int R  = 0;  /* Rows */
        int C = 0; /* Columns */
        int CS = 0; /* Cycle Size */
        int W = 0; /* Width */
        char SC; /* Starting Character */
        
        /* Check for the correct input and print and error statement */
        if(!(cin >> R >> C >> SC >> CS >> W))
            cerr << "r, c, sc, cs, w)" << endl;
        
        if (R == 0 || W == 0 || C == 0 || CS == 0 || CS > 127 || (CS + SC) > 127) return 0;
        
        /* Use SC+(R+C)%CS */
        for (i = 0; i < (R); i++) {
            for (j = 0; j < (W); j++) {
                for (x = 0; x < (C); x++) {
                    for (z = 0; z < (W); z++) { cout << (char)(SC + (i + x) % CS);} } cout << endl;
            }
        }
        
        return 0;
}
