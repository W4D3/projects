all: maze_solve

clean:
	rm -f *.o maze_solve

.SUFFIXES: .cpp .o

.cpp.o: g++ -g -c $*.cpp

maze_solve: maze_solve.o
	g++ -g -o maze_solve maze_solve.o
