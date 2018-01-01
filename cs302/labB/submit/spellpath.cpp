#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

/* spellpath.cpp
   Mitchell Wade
   December 2, 2014

   This program reads in values into a grid that represent
   a game board. Each element of the grid can border up to
   6 other elements in the grid depending upon where it is.
   Using dynamic programming this program will tell you the
   longest path distance you can make from the input.
*/

class spellpath {
    public:
        int MaxPathLen(int r, int c);
        vector <string> grid;
};

int spellpath::MaxPathLen(int r, int c) {

    int rv = 0, max = 0;
    char tmp;

    // Store the selected value
    tmp = grid[r][c];

    // Remove that value
    grid[r][c] = '-';

    // Check South
    if ((r+1 <= grid.size()-1) && ((abs(grid[r+1][c] - tmp)) == 1)) {
        rv = MaxPathLen(r+1, c);

        if (rv > max) max = rv;
    }

    // Check North
    if (((r-1 >= 0) && (abs(grid[r-1][c] - tmp)) == 1)) {
        rv = MaxPathLen(r-1, c);

        if (rv > max) max = rv;
    }
    
    // Check East
    if ((c+1 <= grid[r].size()) && ((abs(grid[r][c+1] - tmp)) == 1)) {
        rv = MaxPathLen(r, c+1);

        if (rv > max) max = rv;
    }
    
    // Check West
    if ((c-1 >= 0) && ((abs(grid[r][c-1] - tmp)) == 1)) {
        rv = MaxPathLen(r, c-1);

        if (rv > max) max = rv;
    }

    // If c is even
    if (c%2 == 0) {
        if ((r+1 <= grid.size()-1) && (c+1 <= grid[r].size()) && (abs(grid[r+1][c+1] - tmp) == 1)) {
            rv = MaxPathLen(r+1, c+1);

            if (rv > max) max = rv;
        }
        
        if ((r+1 <= grid.size()-1) && (c-1 >= 0) && (abs(grid[r+1][c-1] - tmp) == 1)) {
            rv = MaxPathLen(r+1, c-1);

            if (rv > max) max = rv;
        }
    }

    // If c is odd
    if (c%2 != 0) {
        if ((r-1 >= 0) && (c+1 <= grid[r].size()) && (abs(grid[r-1][c+1] - tmp) == 1)) {
            rv = MaxPathLen(r-1, c+1);

            if (rv > max) max = rv;
        }
        
        if ((r-1 >= 0) && (c-1 >= 0) && (abs(grid[r-1][c-1] - tmp) == 1)) {
            rv = MaxPathLen(r-1, c-1);

            if (rv > max) max = rv;
        }
    }

    // Set the value back
    grid[r][c] = tmp;

    return max+1;
}

int main(int argc, char** argv)
{
    int i, j, rv = 0, max = 0;
    spellpath sp;
    string line;

    // Read the values into a grid
    while (cin >> line) {
        sp.grid.push_back(line);
    }

    // Print out the longest path
    for (i = 0; i < sp.grid.size(); i++) {
        for (j = 0; j < sp.grid[i].size(); j++) {
            rv = sp.MaxPathLen(i, j);

            if (rv > max) max = rv;
        }
    }

    cout << max << endl;

	return 0;
}
