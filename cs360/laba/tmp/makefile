#CS 360 Lab-A Makefile

CC = gcc 

INCLUDES = -I/home/plank/cs360/include

CFLAGS = -g $(INCLUDES)

LIBDIR = /home/plank/cs360/objs

LIBS = $(LIBDIR)/libfdr.a $(LIBDIR)/sockettome.o -lpthread

EXECUTABLES: serve1

all: $(EXECUTABLES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

serve1: serve1.o
	$(CC) $(CFLAGS) -o serve1 serve1.o $(LIBS)

clean:
	rm core $(EXECUTABLES) *.o


