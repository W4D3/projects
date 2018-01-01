/* CS360 Example Programs for the Atomic Lecture.
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 *
 * This is openunique_3.c
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
  char *string;

  if (argc != 2) {
    fprintf(stderr, "usage: openunique_3 filename\n");
    exit(1);
  }
    
  filename = argv[1];
  string = "Example string\n";

  fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0);
  if (fd <  0) {
    perror(filename);
    exit(1);
  } 
  write(fd, string, strlen(string));
  close(fd);
  exit(0);
}
