/* CS360 Example Programs for the Atomic Lecture.
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 *
 * This is openunique_1.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

main(int argc, char **argv)
{
  struct stat buf;
  int fd;
  char *filename;
  char *string;

  if (argc != 2) {
    fprintf(stderr, "usage: openunique_1 filename\n");
    exit(1);
  }
    
  filename = argv[1];
  string = "Example string\n";

  if (stat(argv[1], &buf) != 0) {
    fd = open(filename, O_WRONLY | O_CREAT, 0);
    if (fd <  0) {
      perror(filename);
      exit(1);
    } 
    write(fd, string, strlen(string));
    close(fd);
  } else {
    printf("%s already exists -- not opening\n", filename);
  }
  exit(0);
}
