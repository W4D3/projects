#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
using namespace std;

#include "sorting.h"

void usage(const char *s)
{
  cerr << "usage: sort_driver size iterations seed double-check(yes|no) print(yes|no)\n";
  if (s != NULL) cerr << s << endl;
  exit(1);
}

main(int argc, const char **argv)
{
  int size;
  int iterations, it;
  int seed;
  int dc;
  int i;
  int j;
  int print;
  vector <double> v;

  if (argc != 6) usage(NULL);

  if (sscanf(argv[1], "%d", &size) != 1 || size <= 0) usage("Bad size\n");
  if (sscanf(argv[2], "%d", &iterations) != 1 || iterations < 0) usage("Bad iterations\n");
  if (sscanf(argv[3], "%d", &seed) != 1) usage("Bad seed\n");
  if (strcmp(argv[4], "yes") == 0) {
    dc = 1;
  } else if (strcmp(argv[4], "no") == 0) {
    dc = 0;
  } else { 
    usage("Bad double-check\n");
  }
  if (strcmp(argv[5], "yes") == 0) {
    print = 1;
  } else if (strcmp(argv[5], "no") == 0) {
    print = 0;
  } else { 
    usage("Bad print\n");
  }

  srand48(seed);

  v.resize(size);
 
  for (it = 0; it < iterations; it++) {
    for (i = 0; i < size; i++) v[i] = drand48()*10;
    sort_doubles(v, print);
    if (dc) {
      for (i = 0; i < size-1; i++) {
        if (v[i] > v[i+1]) {
          cerr << "V is unsorted at element " << i << endl << endl;
          for (j = 0; j < size; j++) {
            fprintf(stderr, "%d %10.8lf\n", j, v[j]);
          }
          exit(1);
        }
      }
    }
  }
  exit(0);
}
