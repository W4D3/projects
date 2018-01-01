# +mkmake+ -- Everything after this line is automatically generated

EXECUTABLES = elevator_null elevator_part_1 elevator_part_2 reorder double-check

CC = gcc
LIBDIR = /home/plank/cs360/objs
LIBS = $(LIBDIR)/libfdr.a
CFLAGS = -g -I/home/plank/include

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


double-check: double-check.o 
	$(CC) $(CFLAGS) -o double-check double-check.o $(LIBS) -lpthread -lm

reorder: reorder.o 
	$(CC) $(CFLAGS) -o reorder reorder.o $(LIBS) -lpthread -lm

elevator_null: elevator_skeleton.o elevator_null.o finesleep.o
	$(CC) $(CFLAGS) -o elevator_null elevator_skeleton.o elevator_null.o finesleep.o $(LIBS) -lpthread -lm

elevator_part_1: elevator_skeleton.o elevator_part_1.o finesleep.o
	$(CC) $(CFLAGS) -o elevator_part_1 elevator_skeleton.o elevator_part_1.o finesleep.o $(LIBS) -lpthread -lm

elevator_part_2: elevator_skeleton.o elevator_part_2.o finesleep.o
	$(CC) $(CFLAGS) -o elevator_part_2 elevator_skeleton.o elevator_part_2.o finesleep.o $(LIBS) -lpthread -lm

elevator_skeleton.o: elevator.h names.h
elevator.o: elevator.h
