CC = gcc
CFLAGS = -g 
SOCKLIB = sockettome.o


EXECUTABLES = client1 serve1 serve2 alternate minitalk minitalk2

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


client1: client1.o sockettome.o
	$(CC) $(CFLAGS) -o client1 client1.o $(SOCKLIB)

serve2: serve2.o sockettome.o
	$(CC) $(CFLAGS) -o serve2 serve2.o $(SOCKLIB)

serve1: serve1.o sockettome.o
	$(CC) $(CFLAGS) -o serve1 serve1.o $(SOCKLIB)

alternate: alternate.o sockettome.o
	$(CC) $(CFLAGS) -o alternate alternate.o $(SOCKLIB)

minitalk: minitalk.o sockettome.o
	$(CC) $(CFLAGS) -o minitalk minitalk.o $(SOCKLIB)

minitalk2: minitalk2.o sockettome.o
	$(CC) $(CFLAGS) -o minitalk2 minitalk2.o $(SOCKLIB)

