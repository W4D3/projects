//A Dynamic Programming solution for subset scheduling problem
#include <stdio.h>

int schedule[84];
int comb[] = {35, 16, 8, 4, 2, 1, 0}

bool isSchedule(int set[], int n, int sum)
{
   bool subset[sum+1][n+1];

   for (int i = 0; i <= n; i++)
      subset[0][i] = true;

   for (int i = 1; i <= sum; i++)
      subset[i][0] = false;

   // Fill the subset table in botton up manner
   for (int i = 1; i <= sum; i++)
   {
      for (int j = 1; j <= n; j++)
      {
         subset[i][j] = set[i];
         if (i >= set[j-1])
            subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
      }
   }

   for (int i = 0; i <= sum; i++) {
      for (int j = 0; j <= n; j++)
      printf ("%4d", subset[i][j]);
      printf("\n");
   }

   return subset[sum][n];
}

// Driver program to test above function
int main()
{
   int set[] = {1, 2, 3, 4, 5, 6, 7};
   int n = 84;

   subSetCount = isSchedule(set, comb, n, sum = set[i]*subSetSizes[i]);
      if (subSetCount == n)
         printf("Found a lunch schedule");
      else
         printf("No lunch schedule found with given time");
   }
   return 0;
}
