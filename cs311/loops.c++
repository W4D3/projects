#include <iostream>
#include <cstdlib>
#include <cstdio>

int main() {

   int i, j, k, l, m;
   unsigned int friends[7] = {1, 2, 3, 4, 5, 6, 7};
   int icount = 0;
   int jcount = 0;
   int kcount = 0;
   int lcount = 0;
   int mcount = 0;

   for(i = 0; i < 7; i++) {
      printf("Loop i: %d\n", i);
      icount ++;
      for(j = 0; i < j; j++) {
         printf("Loop j: %d\n", j);
         jcount ++;
         for(k = 0; i > j > k; k++) {
            printf("Loop k: %d\n", k);
            kcount ++;
            for(l = 0; i > j > k > l; l++) {
               printf("Loop l: %d\n", l);
               lcount ++;
               for(m = 0; i > j > k > l > m; m++) {
                  printf("Loop m: %d\n", m);
                  mcount ++;
               }
            }
         }
      }
   }

   for (i = 0; i < 84; i++) {
      printf("schedule 1 = %d\n", schedule[i]);
   }
   return 0;
}
