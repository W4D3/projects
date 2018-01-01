ALL = galois_mult galois_divide ii_test is_jls
all: $(ALL)

clean:
	rm -f *.o $(ALL)

galois_mult: galois_mult.o galois_field.o
	g++ -g -O3 -o galois_mult galois_mult.o galois_field.o

galois_divide: galois_divide.o galois_field.o
	g++ -g -O3 -o galois_divide galois_divide.o galois_field.o

ii_test: ii_test.o incremental_inverse.o galois_field.o
	g++ -g -O3 -o ii_test ii_test.o incremental_inverse.o galois_field.o

is_jls: is_jls.o incremental_inverse.o galois_field.o
	g++ -g -O3 -o is_jls is_jls.o incremental_inverse.o galois_field.o

print_pcm: print_pcm.o incremental_inverse.o galois_field.o
	g++ -g -O3 -o print_pcm print_pcm.o incremental_inverse.o galois_field.o

print_failures: print_failures.o incremental_inverse.o galois_field.o
	g++ -g -O3 -o print_failures print_failures.o incremental_inverse.o galois_field.o

test_failures: test_failures.o incremental_inverse.o galois_field.o
	g++ -g -O3 -o test_failures test_failures.o incremental_inverse.o galois_field.o

is_jls.o: galois_field.h incremental_inverse.h
incremental_inverse.o: galois_field.h incremental_inverse.h
ii_test.o: galois_field.h incremental_inverse.h
galois_mult.o: galois_field.h
galois_field.o: galois_field.h

.SUFFIXES: .cpp .o

.cpp.o: 
	g++ -g -c -O3 $*.cpp
