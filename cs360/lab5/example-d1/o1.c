/* CS360 Example Programs for the Atomic Lecture.
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 *
 * This is o1.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

main()
{
  struct stat buf;
  int fd;

  fd = open("f1.txt", O_WRONLY | O_CREAT | O_TRUNC);
  sleep(1);
  printf("Doing chmod\n");
  chmod("f1.txt", 0000);
  sleep(1);
  printf("Doing write\n");
  write(fd, "Hi\n", 3);
}
