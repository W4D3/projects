#include "galois_field.h"

void usage(string s)
{
  fprintf(stderr, "usage: galois_mult a b w\n");
  fprintf(stderr, "       w = 8, 16 or 32\n");
  if (s != "") cerr << endl << s << endl;
  exit(0);
}

main(int argc, char **argv)
{
  int a, b, w;
  Galois_Field *gf;

  if (argc != 4) usage("");

  if (sscanf(argv[3], "%d", &w) != 1) usage("Bad w");
  if (w != 8 && w != 16 && w != 32) usage("Bad w");

  if (w == 8 || w == 16) {
    if (sscanf(argv[1], "%u", &a) != 1 || a >= (1<<w)) usage("Bad a");
    if (sscanf(argv[2], "%u", &b) != 1 || b >= (1<<w)) usage("Bad b");
  } else {
    if (sscanf(argv[1], "%u", &a) != 1) usage("Bad a");
    if (sscanf(argv[2], "%u", &b) != 1) usage("Bad b");
  }
  gf = new Galois_Field(w);

  printf("%u\n", gf->Multiply(a, b));
}
