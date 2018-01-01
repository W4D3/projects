#include <cstdlib>
#include <cstdio>

int main() {

   int i, c;

   c = '9';
   i = 10;

   printf("c = %d\n", c);
   printf("i = %d\n", i);
   printf("c-'0' = %d\n", c-'0');
   printf("c-'0' = %d\n", c-'0');
   printf("i-'0' = %d\n", i-'0');
   printf("c+'0' = %d\n", c+'0');
   printf("i+'0' = %c\n", i+'0');
   printf("c-'0' = %c\n", c-'0');
   printf("c+'A' = %c\n", c+'A');
   printf("c+'a' = %c\n", c+'a');
   printf("i+'A' = %c\n", i+'A');
   printf("i+'a' = %c\n", i+'a');
   printf("c-'0' = %c\n", c-'0');

   return 0;
}
