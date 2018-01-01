#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sockettome.h"

main(int argc, char **argv)
{
    char *un, c, s[1000];
    int port, sock, fd;

    if (argc != 2) {
        fprintf(stderr, "usage: serve1 port\n");
        exit(1);
    }

    port = atoi(argv[1]);
    if (port < 5000) {
        fprintf(stderr, "usage: serve1 port\n");
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
    do {
        if (read(fd, &c, 1) != 1) {
            printf("Socket Closed Prematurely\n");
            exit(0);
        } else putchar(c);
    } while (c != '\n');

    exit(0);
}
