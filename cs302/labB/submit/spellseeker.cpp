#include <iostream>
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

/* spellseeker.cpp
   Mitchell Wade
   December 3, 2014

   This program reads in a grid of values that are offset so that
   there are elements on the grid that can border up to 6 other
   elements. Using dynamic programming and a DFS algorithm this
   program calculates the longest path of values that differ by
   only + or - 1 in value.
*/

class Answer {
    public:
        int length;
        int r;
        int c;
        string key;
        Answer *nexta;
};

class SpellSeeker {
    public:
        vector <string> grid;
        map <string, Answer *> cache;
        int total_r;
        int total_c;

        Answer *Solve(int r, int c);
        void DFS(int r, int c, string &s);
};

void SpellSeeker::DFS(int r, int c, string &s) {

    char tmp;

    // Check if that spot has already been visited
    if (s[r*total_c+c] == 'O') return;

    // Mark current spot
    if (s[r*total_c+c] == '-')
        s[r*total_c+c] = 'O';

    // Store the selected value
    tmp = grid[r][c];

    // Remove that value in the grid
    grid[r][c] = '-';

    // Check South
    if ((r+1 <= total_r-1) && ((abs(grid[r+1][c] - tmp)) == 1)) {
        DFS(r+1, c, s);
    }

    // Check North
    if (((r-1 >= 0) && (abs(grid[r-1][c] - tmp)) == 1)) {
        DFS(r-1, c, s);
    }

    // Check East
    if ((c+1 <= total_c) && ((abs(grid[r][c+1] - tmp)) == 1)) {
        DFS(r, c+1, s);
    }

    // Check West
    if ((c-1 >= 0) && ((abs(grid[r][c-1] - tmp)) == 1)) {
        DFS(r, c-1, s);
    }

    // If c is even
    if (c%2 == 0) {
        if ((r+1 <= total_r-1) && (c+1 <= total_c) && (abs(grid[r+1][c+1] - tmp) == 1)) {
            DFS(r+1, c+1, s);
        }

        if ((r+1 <= total_r-1) && (c-1 >= 0) && (abs(grid[r+1][c-1] - tmp) == 1)) {
            DFS(r+1, c-1, s);
        }
    }

    // If c is odd
    if (c%2 != 0) {
        if ((r-1 >= 0) && (c+1 <= total_c) && (abs(grid[r-1][c+1] - tmp) == 1)) {
            DFS(r-1, c+1, s);
        }

        if ((r-1 >= 0) && (c-1 >= 0) && (abs(grid[r-1][c-1] - tmp) == 1)) {
            DFS(r-1, c-1, s);
        }
    }

    // Set the value back in the grid
    grid[r][c] = tmp;

    return;
}

Answer *SpellSeeker::Solve(int r, int c) {

    char tmp;
    string s;
    Answer *rv, *max, *a;

    // Create the key
    s.resize(total_r*total_c, '-');

    // Call DFS to fill in the key
    DFS(r, c, s);

    // Set the initial spot
    s[r*total_c+c] = 'X';

    // Initialize the temporary max pointer
    max = NULL;

    // Check if that key already exists
    if (cache.find(s) != cache.end()) return cache[s];

    // Create the Answer pointer
    a = new Answer;
    a->length = 1;
    a->r = r;
    a->c = c;
    a->key = s;
    a->nexta = NULL;

    // Store the selected value
    tmp = grid[r][c];

    // Remove that value in the grid
    grid[r][c] = '-';

    // Check South
    if ((r+1 <= total_r-1) && ((abs(grid[r+1][c] - tmp)) == 1)) {
    
        rv = Solve(r+1, c);

        if (max == NULL || rv->length > max->length) max = rv;
    }

    // Check North
    if (((r-1 >= 0) && (abs(grid[r-1][c] - tmp)) == 1)) {
        rv = Solve(r-1, c);

        if (max == NULL || rv->length > max->length) max = rv;
    }

    // Check East
    if ((c+1 <= total_c) && ((abs(grid[r][c+1] - tmp)) == 1)) {
        rv = Solve(r, c+1);

        if (max == NULL || rv->length > max->length) max = rv;
    }

    // Check West
    if ((c-1 >= 0) && ((abs(grid[r][c-1] - tmp)) == 1)) {
        rv = Solve(r, c-1);

        if (max == NULL || rv->length > max->length) max = rv;
    }

    // If c is even
    if (c%2 == 0) {
        if ((r+1 <= total_r-1) && (c+1 <= total_c) && (abs(grid[r+1][c+1] - tmp) == 1)) {
            rv = Solve(r+1, c+1);

            if (max == NULL || rv->length > max->length) max = rv;
        }

        if ((r+1 <= total_r-1) && (c-1 >= 0) && (abs(grid[r+1][c-1] - tmp) == 1)) {
            rv = Solve(r+1, c-1);

            if (max == NULL || rv->length > max->length) max = rv;
        }
    }

    // If c is odd
    if (c%2 != 0) {
        if ((r-1 >= 0) && (c+1 <= total_c) && (abs(grid[r-1][c+1] - tmp) == 1)) {
            rv = Solve(r-1, c+1);

            if (max == NULL || rv->length > max->length) max = rv;
        }

        if ((r-1 >= 0) && (c-1 >= 0) && (abs(grid[r-1][c-1] - tmp) == 1)) {
            rv = Solve(r-1, c-1);

            if (max == NULL || rv->length > max->length) max = rv;
        }
    }

    // Set the value back in the grid
    grid[r][c] = tmp;

    // Initialize nexta
    a->nexta = max;

    if (max != NULL) a->length = max->length+1;

    // Return the Answer of the key and set it in the cache
    return cache[s] = a;
}

int main(int argc, char** argv)
{
    int i, j;
    SpellSeeker ss;
    string line, s;
    Answer *rv, *max;

    // Read the values into a grid
    while (cin >> line) {
        ss.grid.push_back(line);
    }

    // Set the spellseekers total rows and columns
    ss.total_r = ss.grid.size();
    ss.total_c = ss.grid[0].size();

    // Print out the initial grid
    for (i = 0; i < ss.grid.size(); i++) {
        for (j = 0; j < ss.grid[i].size(); j++) {
            cout << ss.grid[i][j];
        }
        cout << endl;
    }

    // Print out the path
    cout << "PATH" << endl;

    // Initialize the temporary max pointer
    max = NULL;

    // Find the longest path
    for (i = 0; i < ss.grid.size(); i++) {
        for (j = 0; j < ss.grid[i].size(); j++) {
            rv = ss.Solve(i, j);

            if (max == NULL || rv->length > max->length) max = rv;
        }
    }

    // Print out the path
    while (max != NULL) {
        cout << max->r << " " << max->c << endl;
        max = max->nexta;
    }

    return 0;
}
