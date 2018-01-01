#include <stdio.h>
#include <stdlib.h>
#include "fields.h"

main(int argc, char **argv)
{ 
  int i;
  IS is;

  if (argc == 1) {
    is = new_inputstruct(NULL);
    while (get_line(is) >= 0) {
      fprintf(stderr, "%s", is->text1);
      fflush(stderr);
    }
    exit(0);
  }

  for (i = 1; i < argc; i++) {
    is = new_inputstruct(argv[i]);
    if (is == NULL) { perror(argv[i]); exit(1); }
    while (get_line(is) >= 0) {
      fprintf(stderr, "%s", is->text1);
      fflush(stderr);
    }
    jettison_inputstruct(is);
  }
  exit(0);
}
