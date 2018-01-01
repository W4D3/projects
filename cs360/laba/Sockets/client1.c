#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sockettome.h"

main(int argc, char **argv)
{
  char *hn, *un;
  int port, fd;
  char s[1000];
  FILE *fin, *fout;

  if (argc != 3) { fprintf(stderr, "usage: client1 hostname port\n"); exit(1); }

  hn = argv[1];
  port = atoi(argv[2]);
  un = getenv("USER");

  fd = request_connection(hn, port);

  printf("Connection established.  Receiving:\n\n");

  fin = fdopen(fd, "r");
  fout = fdopen(fd, "w");

  if (fgets(s, 1000, fin) == NULL) {
    printf("Server closed prematurely\n");
    exit(0);
  }

  printf("Received: %s", s);
  printf("Sending `Client: %s' to the server\n", un);
  fprintf(fout, "Client: %s\n", un);
  exit(0);
}
