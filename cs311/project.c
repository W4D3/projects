// A Dynamic Programming based solution for schedule subsets problem
#include <stdio.h>
#include <bits/stdc++.h>

int schedule[84];
int comb[] = {35, 16, 8, 4, 2, 1};
int friends[] = {1, 2, 3, 4, 5, 6, 7};   // Integer rep.

// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }
int intToBit(int n) {return (1 << n) }

int scheduleSubset(int set[], int size)
{
   int bits; 
   qsort(set, size, max);

   for (i = 0; i < 7; i++) {
      bits = intToBit(set[i]);
      
   delete[] table;

   return result;
}

int main()
{
   int i;
   int set[] = {1, 3, 7, 15, 31, 63, 127};  // Integer rep. of bits

   for (i = 0; i < 84; i++) {
      int size = sizeof(set)*sizeof(comb[i]);
      printf("%d\n", scheduleSubset(set, size);
   }

   return 0;
}
