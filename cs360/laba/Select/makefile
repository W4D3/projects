CC = gcc
CSDIR = /home/plank/cs360
CFLAGS = -g -I$(CSDIR)/include
SOCKLIB = $(CSDIR)/objs/sockettome.o -lnsl


EXECUTABLES = jtelnet 

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


jtelnet: jtelnet.o
	$(CC) $(CFLAGS) -o jtelnet jtelnet.o $(SOCKLIB)
