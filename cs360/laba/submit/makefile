#CS 360 Lab-A Makefile

CC = gcc 

INCLUDES = -I/home/plank/cs360/include

CFLAGS = -g $(INCLUDES)

LIBDIR = /home/plank/cs360/objs

LIBS = $(LIBDIR)/libfdr.a $(LIBDIR)/sockettome.o -lpthread

EXECUTABLES: chat_server

all: $(EXECUTABLES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

chat_server: chat_server.o
	$(CC) $(CFLAGS) -o chat_server chat_server.o $(LIBS)

clean:
	rm core $(EXECUTABLES) *.o


