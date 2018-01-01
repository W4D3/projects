/* Forkcat2.c */

#include <stdio.h>
#include <fcntl.h>

/* This program fork off a process that calls

  cat /home/plank/cs360/lab9/forkcat1.c

  and redirects the output to the file "catoutput".  This is just like
  forkcat1.c except that it first opens the output file as file descriptor 1.

*/

main(int argc, char **argv)
{
  int status;
  char **newargv;
  int fd;

  newargv = (char **) malloc(sizeof(char *)*3);

  newargv[0] = "cat";
  newargv[1] = "/home/plank/cs360/notes/Dup/dupex2.c";
  newargv[2] = NULL;

  if (fork() == 0) {
    fd = open("catoutput", O_WRONLY | O_TRUNC | O_SYNC | O_CREAT, 0666);
    if (fd < 0) {
      perror("forkcat1: catoutput");
      exit(1);
    }
    dup2(fd, 1);
    close(fd);
    execvp("cat", newargv);
    perror("forkcat1");
    exit(1);
  } else {
    wait(&status);
  }
}
