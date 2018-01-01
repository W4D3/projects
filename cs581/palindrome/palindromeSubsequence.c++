// palindromeSubsequence.c++
// Mitchell Wade
// March 10th, 2016
// This program finds the longest palindrome subsequence of the original 
// input string that it is given as well as finding the longest palindrome 
// subsequence from the statement of the Principle of Optimality by Richard 
// Bellman (ignoring whitespace and punctuation, but not capitalization):
//
//  An optimal policy has the property that whatever the initial state and
//  initial decision are, the remaining decisions must constitute an optimal
//  policy with regard to the state resulting from the first decision.
//
// The program also uses dynamic programming in order to increase the speed 
// of the algorithm. It also computes the running time of the algorithm and 
// displays that to the user via a text file that can be used to fit a curve
// for the resulting data points of the algorithms complexity.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

typedef vector <char*> CVec;

//string optimas = "Anoptimalpolicyhasthepropertythatwhatevertheinitialstateandinitaldecisionare,theremainingdecisionsmustconstituteanoptimalpolicywithregardtothestateresultingfromthefirstdecision";

// Finds max of two integers
int max(int a, int b) { return (a > b) ? a: b; }

// Longest palindromic subsequence algorithm
int lps(char *s, int i, int j) 
{
   int cl = 0;          // Iteration variables
   int n = strlen(s);   // Full length of string
   char DP[n][n];     // DP Table
   int str[n];          // Temporary string for comparing subsequences

   // Use an array of unsigned ints/chars
   for (i = 0; i < n; i++) {
      DP[i][i] = 1;
   }

   for (cl = 0; cl <= n; cl++) {
      for (i = 0; i < n-cl+1; i++) {
         j = i+cl-1;

         // A length of string 2 with proper index of l
         if (str[i] == str[j] && cl == 2) {
            DP[i][j] = 2;
         // If both strings are the same
         } else if (str[i] == str[j]) {
            DP[i][j] = DP[i+1][j-1] + 2;
         // return the indexes of the maximum search
         } else {
            DP[i][j] = max(DP[i][j-1], DP[i+1][j]);
         }
      }
   }

   return DP[0][n-1];
}

int main(int argc, char*argv[]) {
   char s[1000000];
   char rv[10000000];
   int n = 0;

   if (argc != 2 || argc != 3) {
      printf("usage: lps [-optimalitystring] string\n");
      exit(1);
   }
   
   if (argc == 2) {
      n = strlen(argv[2]);
      rv = lps(s, 0, n-1);
   } //else {
      //n = strlen(argv[3]);
      //rv = lps(optimas, 0, n-1);
   //}

   printf("The length of the LPS is %d"), rv;

   printf("Press any key to exit: ");
   getchar();
   return 0;
}
