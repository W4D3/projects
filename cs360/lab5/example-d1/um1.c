/* CS360 Example Programs for the Atomic Lecture.
 *
 * James S. Plank
 * University of Tennessee
 * February, 2010
 *
 * This is um1.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

main()
{
  int fd;
  int old_mask;

  old_mask = umask(0);
  printf("The old mask was 0%o\n", old_mask);

  fd = open("f1", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  close(fd);
  printf("created f1: 0666\n");
  fd = open("f2", O_WRONLY | O_CREAT | O_TRUNC, 0200);
  close(fd);
  printf("created f2: 0200\n");

  umask(022);
  fd = open("f3", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  close(fd);
  printf("created f3: 0%o\n", 0666 & ~022 & 0777);
  fd = open("f4", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  close(fd);
  printf("created f4: 0%o\n", 0777 & ~022 & 0777);
  fd = open("f5", O_WRONLY | O_CREAT | O_TRUNC, 0200);
  close(fd);
  printf("created f5: 0%o\n", 0200 & ~022 & 0777);
}

