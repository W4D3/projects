/* CS360 Example Programs for the Atomic Lecture.
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 *
 * This is openunique_4.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

main(int argc, char **argv)
{
  int fd;
  char *filename;
  int iterations, i;
  int successful, unsuccessful, erroneous;

  if (argc != 3) {
    fprintf(stderr, "usage: openunique_4 filename iterations\n");
    exit(1);
  }
    
  filename = argv[1];
  iterations = atoi(argv[2]);
  successful = 0;
  unsuccessful = 0;
  erroneous = 0;

  for (i = 0; i < iterations; i++) {
    fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0);
    if (fd < 0 && errno == EEXIST) {
      unsuccessful++;
    } else if (fd < 0) {
      perror(filename);
      exit(1);
      erroneous++;
    } else {
      close(fd);
      remove(filename);
      successful++;
    }
  }
  printf("  Successful: %5d\n", successful);
  printf("Unsuccessful: %5d\n", unsuccessful);
  printf("   Erroneous: %5d\n", erroneous);
  exit(0);
}
