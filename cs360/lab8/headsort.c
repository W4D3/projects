/* headsort.c --  does "head -5 headsort.c | sort" */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

main()
{
  int dummy2, dummy1, i;
  int pipefd[2];

  i = pipe(pipefd);
  if (i < 0) {
    perror("headsort: pipe");
    exit(1);
  }

  if (fork() == 0) {
    if (dup2(pipefd[1], 1) != 1) {
      perror("headsort: dup2(pipefd[1])");
      exit(1);
    }
    close(pipefd[1]);
    close(pipefd[0]);
    fprintf(stderr, "Execcing head\n");
    execlp("head", "head", "-5", "headsort.c", NULL);
    perror("headsort: exec head failed");
    exit(1);
  } else if (fork() == 0) {
    if (dup2(pipefd[0], 0) != 0) {   
      perror("headsort: dup2(pipefd[0])");
      exit(1);
    }
    close(pipefd[1]);
    close(pipefd[0]);
    printf("Execcing sort\n");
    execlp("sort", "sort", NULL);
    perror("headsort: exec sort failed");
    exit(1);
  } else {
    close(pipefd[1]);
    close(pipefd[0]);
    wait(&dummy1);
    wait(&dummy2);
    if (WEXITSTATUS(dummy1) || WEXITSTATUS(dummy2)) {
      fprintf(stderr, "Abnormal exit.\n");
    }
  }
}
