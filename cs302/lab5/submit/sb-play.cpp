#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "DJ.h"
#include <map>
using namespace std;

/* 
   sb-play.cpp
   Mitchell Wade
   October 23, 2014

   This program simulates playing the game Superball. It
   uses disjoint sets to hold connected component of a
   game board, scores the connected component if possible,
   and also prints out either each swap between cells or
   a selected scoring call on the game board.
*/

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
    public:
        Superball(int argc, char **argv);
        int r;
        int c;
        int mss;
        int empty;
        vector <int> board;
        vector <int> goals;
        vector <int> colors;
        int analyze_superball();
        void score_superball();
};

// Combines the disjoint sets, figures out if you can score, and
// returns the maximum score possible
int Superball::analyze_superball() {

    Disjoint dj(r*c);
    int i = 0;
    map <int, int> size;

    // Combine the disjoint sets
    for (i = 0; i < r*c; i++) {

        // Check Right
        // Make sure it doesn't loop to the next row
        // Check to see if the colors are the same
        if ((i%c != c-1) && board[i+1] == board[i]) {

            // If they are not joined yet, conjoin them
            if (dj.Find(i+1) != dj.Find(i)) {
                dj.Union(dj.Find(i+1), dj.Find(i));
            }
        }

        // Check Below
        // Make sure it doesn't loop to the next column
        // Check to see if the colors are the same
        if ((i/c != r-1) && board[i+c] == board[i]) {

            // If they are not joined yet, conjoin them
            if (dj.Find(i+c) != dj.Find(i)) {
                dj.Union(dj.Find(i+c), dj.Find(i));
            }
        }
    }

    // Calculate size
    for (i = 0; i < r*c; i++) {
        size[dj.Find(i)]++;
    }

    int score, max = 0;

    // Find the maximum scoring set on the board
    for (i = 0; i < r*c; i++) {
        // If it is in a goal cell and it is greater than the 
        // minimum score size print out the scoring sets
        if ((goals[i] == 1) && (board[i] != '*')) {

            // Calculates the score of the set selected
            score = size[dj.Find(i)] * colors[board[i]];

            // Keeps track of the maximum score
            if(score > max){
                max = score;
            }
        }
    }
    return max;
}

// Prints out the score selected
void Superball::score_superball() {

    Disjoint dj(r*c);
    int i = 0;
    map <int, int> size;

    // Combine the disjoint sets
    for (i = 0; i < r*c; i++) {

        // Check Right
        // Make sure it doesn't loop to the next row
        // Check to see if the colors are the same
        if ((i%c != c-1) && board[i+1] == board[i]) {

            // If they are not joined yet, conjoin them
            if (dj.Find(i+1) != dj.Find(i)) {
                dj.Union(dj.Find(i+1), dj.Find(i));
            }
        }

        // Check Below
        // Make sure it doesn't loop to the next column
        // Check to see if the colors are the same
        if ((i/c != r-1) && board[i+c] == board[i]) {

            // If they are not joined yet, conjoin them
            if (dj.Find(i+c) != dj.Find(i)) {
                dj.Union(dj.Find(i+c), dj.Find(i));
            }
        }
    }

    // Calculate size
    for (i = 0; i < r*c; i++) {
        size[dj.Find(i)]++;
    }

    int score, max = -1;
    int maxpos  = -1;

    for (i = 0; i < r*c; i++) {
        
        // If the set is in a goal cell, bigger than the min.
        // score size, and a correct scorable cell store it
        // as the maximum score possible
        if ((goals[i] == 1) && (size[dj.Find(i)] >= mss) && (board[i] != '*')) {
            score = size[dj.Find(i)] * colors[board[i]];
            
            // Check for a higher score
            if(score > max){
                max = score;
                maxpos = i;
            }
        }
    }

    // Print out the selected scoring of a set
    if(maxpos != -1) {
        printf("SCORE %d %d\n", maxpos / c, maxpos % c);
        exit(1);
    }
}
void usage(const char *s) 
{
    fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
    if (s != NULL) fprintf(stderr, "%s\n", s);
    exit(1);
}

Superball::Superball(int argc, char **argv)
{
    int i, j;
    string s;

    if (argc != 5) usage(NULL);

    if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
    if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
    if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

    colors.resize(256, 0);

    for (i = 0; i < strlen(argv[4]); i++) {
        if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
        if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
        if (colors[argv[4][i]] != 0) usage("Duplicate color");
        colors[argv[4][i]] = 2+i;
        colors[toupper(argv[4][i])] = 2+i;
    }

    board.resize(r*c);
    goals.resize(r*c, 0);

    empty = 0;

    for (i = 0; i < r; i++) {
        if (!(cin >> s)) {
            fprintf(stderr, "Bad board: not enough rows on standard input\n");
            exit(1);
        }
        if (s.size() != c) {
            fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
            exit(1);
        }
        for (j = 0; j < c; j++) {
            if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
                fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
                exit(1);
            }
            board[i*c+j] = s[j];
            if (board[i*c+j] == '.') empty++;
            if (board[i*c+j] == '*') empty++;
            if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
                goals[i*c+j] = 1;
                board[i*c+j] = tolower(board[i*c+j]);
            }
        }
    }
}

int main(int argc, char **argv)
{
    Superball *s;
    int i, j;
    int ngoal, tgoal;
    int score, max = -1;
    int maxi, maxj;
    vector <int> tmp;

    s = new Superball(argc, argv);

    // If the board only has 5 cells remaining, score the largest set
    if(s->empty < 5) {
        s->score_superball();
    }

    tmp.resize(1);
    // Figures out if you can score and combines the disjoint sets
    for(i=0; i<s->board.size(); i++) {
        if(s->board[i] == '.' || s->board[i] == '*') continue;
        for(j=i+1; j<s->board.size(); j++) {
            if(s->board[j] == '.' || s->board[j] == '*') continue;
            
            // Swap the cells
            tmp[0] = s->board[i];
            s->board[i] = s->board[j];
            s->board[j] = tmp[0];

            // Calculate the max score
            score = s->analyze_superball();
            if(score > max) {
                max = score;
                maxi = i;
                maxj = j;
            }

            // Swap the cells back
            tmp[0] = s->board[j];
            s->board[j] = s->board[i];
            s->board[i] = tmp[0];
        }
    }

    // Print out each selected swap
    printf("SWAP %d %d %d %d\n", maxi/s->c, maxi%s->c, maxj/s->c, maxj%s->c);
    exit(0);
}
