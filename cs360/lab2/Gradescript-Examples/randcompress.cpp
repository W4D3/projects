#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

main(int argc, char **argv)
{
  int i, j, k, tj, tk, tl, l, type, x, exp;
  double d, dexp;
  string types, a4;
  int ssizes, sit, bit;
  int iterations;
  int maxsize;
  string chars = "ABCDEFGHIJKLMNOPQURSTUVWXYZabcdefghijklmnopqrstuvwxyz-_,.;':<>/?`~";

  if (argc != 5) {
    cerr << "usage: randcompress iterations types(ids) maxsize(anything) ssizes(number or ONLY-256)\n";
    exit(1);
  }

  iterations = atoi(argv[1]);
  types = argv[2];
  maxsize = atoi(argv[3]);
  ssizes = atoi(argv[4]);
  a4 = argv[4];
  if (a4 == "ONLY-256") ssizes = -1;
    
  srand48(time(0));

  for (i = 0; i < iterations; i++) {
    tj = lrand48()%types.size();
    bit = lrand48()%maxsize+1;
    for (j = 0; j < bit; j++) {
      if (types[tj] == 'i') {
        printf(" %ld", lrand48()%1000000000);
      } else if (types[tj] == 'd') {
        printf(" %.10lg", drand48()*exp2(drand48()*12.0));
      } else {
        printf(" ");
        sit = (ssizes == -1) ? 256 : lrand48()%ssizes+1;
        for (k = 0; k < sit; k++) {
          printf("%c", chars[lrand48()%chars.size()]);
        }
      }
    }
    if (lrand48()%4 == 0) printf("\n");
  }
  printf("\n");
}
