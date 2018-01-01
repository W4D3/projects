/* CS360 Example Programs for the Atomic Lecture.
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 *
 * This is o2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

main()
{
  int fd;
  char s[11];
  int i;

  strcpy(s, "Fun Fun\n");
  fd = open("f1.txt", O_RDONLY);
  sleep(1);
  printf("Removing f1.txt\n");
  remove("f1.txt");
  sleep(1);
  system("ls -l f1.txt");
  i = read(fd, s, 10);
  s[i] = '\0';
  printf("Read returned %d: %d %s\n", i, fd, s);
}
