all: merge_1_sort quick_2_sort

clean: 
	rm -f *.o quick_2_sort merge_1_sort

CFLAGS = -O

.SUFFIXES: .cpp .o
.cpp.o:
	g++ $(CFLAGS) -c $*.cpp

merge_1_sort: merge_1_sort.o sort_driver.o
	g++ $(CFLAGS) -o merge_1_sort merge_1_sort.o sort_driver.o

quick_2_sort: quick_2_sort.o sort_driver.o
	g++ $(CFLAGS) -o quick_2_sort quick_2_sort.o sort_driver.o

