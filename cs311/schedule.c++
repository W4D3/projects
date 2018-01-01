#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

void Convert(unsigned int[]){

   char buf[99];
   e0 << f012345;
   e1 << f012346;
   e2 << f012356;
   e3 << f012456;
   e4 << f013456;
   e5 << f023456;
   e6 << f123456;
   printf("%d, %d, %d, %d, %d, %d, %d\n", e0, e1, e2, e3, e4, e5, e6);

   for(i = 0; i < 7; i++) {
      n = schedule[i];

      while(t--)
      {
         for(int l=0; l<n; l++) cin >> buf[l];
         for(int i=0; i<(1<<n); i++)
         {
            for(int j=0; j<n; j++)
               if(i & (1 << j))
                  pf("%c", buf[j]);
            pf("\n");
         }
      }
   }
}

int main() {

   int schedule[84];
   //int friends = {0,1,2,3,4,5,6};
   unsigned int f012345 = 63;
   unsigned int f012346 = 95;
   unsigned int f012356 = 111;
   unsigned int f012456 = 119;
   unsigned int f013456 = 123;
   unsigned int f023456 = 125;
   unsigned int f123456 = 126;

   // Print subsets of size 6
   // printf("%d, %d, %d, %d, %d, %d, %d\n", f012345, f012346,
   //        f012356, f012456, f013456, f023456, f123456);

   schedule[0] = f012345;
   schedule[1] = f012346;
   schedule[2] = f012356;
   schedule[3] = f012456;
   schedule[4] = f013456;
   schedule[5] = f023456;
   schedule[6] = f123456;

   Subsets(schedule[i]);

   return 0;
}
