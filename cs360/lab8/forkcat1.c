/* Forkcat1.c */

#include <stdio.h>

/* This program forks off a process that calls

  cat /home/plank/cs360/notes/Dup/dup2ex.c

  forkcat1.c waits for its child to finish executing before exiting
*/

main(int argc, char **argv)
{
  int pid, status;
  char **newargv;

  newargv = (char **) malloc(sizeof(char *)*3);

  newargv[0] = "cat";
  newargv[1] = "/home/plank/cs360/notes/Dup/dup2ex.c";
  newargv[2] = NULL;

  if (fork() == 0) {
    execvp("cat", newargv);
    perror("forkcat1");
    exit(1);
  } else {
    wait(&status);
  }
}
