#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sockettome.h"

main(int argc, char **argv)
{
  char *un;
  int port, sock, fd;
  int i;
  char s[1000];
  FILE *fsock;

  if (argc != 2) {
    fprintf(stderr, "usage: serve2 port\n");
    exit(1);
  }

  port = atoi(argv[1]);
  if (port < 5000) {
    fprintf(stderr, "usage: serve2 port\n");
    fprintf(stderr, "       port must be > 5000\n");
    exit(1);
  }
  un = getenv("USER");

  sock = serve_socket(port);

  fd = accept_connection(sock);

  printf("Connection established.  Sending `Server: %s'\n", un);
  sprintf(s, "Server: %s\n", un);
  write(fd, s, strlen(s));

  printf("Receiving:\n\n");

  fsock = fdopen(fd, "r");

  if (fgets(s, 1000, fsock) == NULL) {
    printf("Error -- socket closed\n");
  } else {
    printf("%s", s);
  }
}
