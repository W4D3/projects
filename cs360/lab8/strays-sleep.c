#include <stdio.h>
#include <stdlib.h>
#include "fields.h"

main(int argc, char **argv)
{ 
  IS is;
  int i;
  int c;
  int counter;
  FILE *f;
  char buf[1000];

  for (i = 3; i < 64; i++) {
    if (close(i) == 0) fprintf(stderr, "FD %d was open\n", i);
  }
  usleep(200000);
  counter = 0;
  if (argc == 1) {
    while((c = getchar()) != EOF) {
      putchar(c);
      counter++;
      if (counter % 50 == 0) fflush(stdout);
    }
    exit(0);
  }
  for (i = 1; i < argc; i++) {
    f = fopen(argv[i], "r");
    if (f == NULL) { perror(argv[i]); exit(1); }
    do {
      c = fread(buf, 1, 1000, f);
      if (c > 0) { fwrite(buf, 1, c, stdout); fflush(stdout); }
    } while (c > 0);
    fclose(f);
  }
}
