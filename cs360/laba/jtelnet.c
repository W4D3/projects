/* jtelnet.c
   Jim Plank
   CS360
   Select Lecture
   */

#include "sockettome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

main(int argc, char **argv)
{
  int port;
  int fd;
  char *hostname, buf[100];
  fd_set readfds, masterfds;                            
  int nopen, n;

  if (argc != 3) {
    fprintf(stderr, "usage: jtelnet host port\n");
    exit(1);
  }

  hostname = argv[1];
  port = atoi(argv[2]);

  fd = request_connection(hostname, port);

  FD_ZERO(&masterfds);
  FD_SET(0, &masterfds);
  FD_SET(fd, &masterfds);
  
  while (1) {
    memcpy(&readfds, &masterfds, sizeof(fd_set));

    if (select(fd+1, &readfds, NULL, NULL, NULL) < 0) {
      perror("on select");
      exit(1);
    }

    if (FD_ISSET(0, &readfds)) {
      n = read(0, buf, 100);
      if (n == 0) {
        close(0);
        close(fd);
        exit(1);
      } else {
        write(fd, buf, n);
      }
    } else if (FD_ISSET(fd, &readfds)) {
      n = read(fd, buf, 100);
      if (n == 0) {
        close(0);
        close(fd);
        exit(1);
      } else {
        write(1, buf, n);
      }
    }
  }
}
