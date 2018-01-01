/* ==================================================================
 *
 * CS 160 (Gregor) -- arm2: Sorting an array 
 *
 * sortmain.cpp
 *
 * C++ program that populates lists to be manipulated/sorted by
 * three external ARM assembly routines (found in 'asmsort.s').
 * ================================================================== */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

void createList(char *list, int N) 
{
  int i;
  for (i=0; i<N; i++)
    list[i] = rand() & 0xff;
}

void printList(const char *text, char *list, int N) {
  int i;

  cout << text << ": ";
  for (i = 0; i < N; i++)
	cout << setw(3) << (int)list[i] << " ";
  cout << endl;
}

// Reference external ARM assembly routines...
extern "C" void sort1 (char *A, char *B, int N);
extern "C" void sort2 (char *A, int N);
extern "C" void sort3 (char *A, int N);

int main (int argc, char *argv[]) {
  srand(time(NULL));

  int N = 10;
  if (argc > 1) N = atoi(argv[1]);

  char listA[N], listB[N], listC[N];

  createList(listA, N);
  createList(listB, N);
  memcpy(listC, listB, sizeof(char) * N);

  cout << "\nInitial data\n" << endl;

  printList("List A", listA, N);
  printList("List B", listB, N);
  printList("List C", listC, N);

  cout << "\nSorted data\n" << endl;
  sort1(listA, listB, N);
  printList("List A", listA, N);

  sort2(listB, N);
  printList("List B", listB, N);

  sort3(listC, N);
  printList("List C", listC, N);
}
