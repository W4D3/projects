# CS 360 Lab 8 Makefile
# Mitchell Wade
# April 10, 2015
# This gradescript includes Dr. Plank's directories, 
# libraries, and complies jsh1, jsh2, and jsh3.

CC = gcc

EXECUTABLES = jsh1 jsh2 jsh3

INCLUDES = -I/home/plank/cs360/include

CFLAGS = -g $(INCLUDES)

LIBDIR = /home/plank/cs360/objs

LIBS = $(LIBDIR)/libfdr.a

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


jsh1: jsh1.o
	$(CC) $(CFLAGS) -o jsh1 jsh1.o $(LIBS)

jsh2: jsh2.o
	$(CC) $(CFLAGS) -o jsh2 jsh2.o $(LIBS)

jsh3: jsh3.o
	$(CC) $(CFLAGS) -o jsh3 jsh3.o $(LIBS)

