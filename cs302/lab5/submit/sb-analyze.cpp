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
   sb-analyze.cpp
   Mitchell Wade
   October 23, 2014

   This program prints out all possible scoring sets
   that are on the gameboard. It uses a disk joint
   set to keep track of the connected cells and
   prints it out.
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
    void analyze_superball();
};

void Superball::analyze_superball() {

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
    
    printf("Scoring sets:\n");
    // Print out the DJ sets
    for (i = 0; i < r*c; i++) {

        // If it is in a goal cell and it is greater than the 
        // minimum score size print out the scoring sets
        if ((goals[i] == 1) && (size[dj.Find(i)] >= mss) && (board[i] != '*')) {

            printf("  Size: %2d Char: %2c Scoring Cell: %d,%d\n", size[dj.Find(i)], board[i], i/c, i%c);
        
            // Makes sure that it doesn't print out duplicates
            size[dj.Find(i)] = 0;
        }
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

main(int argc, char **argv)
{
  Superball *s;
  int i, j;
  int ngoal, tgoal;
 
  s = new Superball(argc, argv);

  // Prints out the scoring sets
  s->analyze_superball();

  exit(0);
}
