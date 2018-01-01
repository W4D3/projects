// palindromeSubsequence.c++
// Mitchell Wade
// March 10th, 2016
// This program finds the longest palindrome in which is a 
// subsequence of the original input string that it is given as well
// as finding the longest palindrome subsequence from the statement of 
// the Principle of Optimality by Richard Bellman (ignoring whitespace,
// and punctuation, but not capitalization):
//  An optimal policy has the property that whatever the initial state and
//  initial decision are, the remaining decisions must constitute an optimal
//  policy with regard to the state resulting from the first decision.
//
// The progrma also uses dynamic programming in order to speed
// up the run time of the program as well as reducing the amount
// of space that is needed in order to compute the algorithm. It 
// also computes the running time of the algorithm and displays 
// that to the user via a text file that can be used to fit a curve
// for the resulting data points of the algorithms complexity.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

typedef vector <string> SVec;

/*string classifyIt(string w);

string classifyIt(string w) {
   int i = 0, j = 0, ispal = 0;
   string t;

   i = 0;
   j = w.size()-1;
   ispal = 1;
   while (i < j) {
      if (w[i] != w[j]) ispal = 0;
      i++;
      j--;
   }
   if(ispal) return "PALINDROME";

   t.push_back(w[0]);
   for(i=1; i<w.size(); i++) {
      if(w[i] != w[i-1]) t.push_back(w[i]);
   }
   i = 0;
   j = t.size()-1;
   cout << w << " " < t << endl;
   while( i < j) {
      if(t[i] != t[j]) return "NOT EVEN FAUX";
      j++;
      j--;
   };
   return "FAUX";
}*/

int main(int argc, char*argv[]) {

   //ifstream f;
   string originalString, subString, principleOfOptimality;

   principleOfOptimality = "Anoptimalpolicyhasthepropertythatwhatevertheinitialstateandinitaldecisionare,theremainingdecisionsmustconstituteanoptimalpolicywithregardtothestateresultingfromthefirstdecision";

   cout << principleOfOptimality;
   /*
   if (argv != ?) {
      printf("usage: palindrome_subsequence inputFile\n")
      exit(1);
   }

   f.open(argv[2], ios::in);
   if(myfile.is_open()) {
      while(getline(myfile, line)) {
         s << line << '\n';
   } else {
      ferror("file did not open correctly\n"); 
   }*/

i  cout << "Enter string for testing: ";
   cin >> originalString;

   cout << "Palidrome Subsequence = " << subString << endl;
   cout << "Press enter to exit" <<endl;
   cin.get();

   //f.close();
   return 0;
}

string longestSubPalindrome(const string& a_string)
{
   unsigned int ui;
   // Type composing DP table. First ui is the length of the longest
   // subpalindrome, next ui is the index of the parent table index, the
   // char is the character added to the subpalindrome at the table entry
   // (char is null if no character was added)
   
   unsigned int uiT = tuple<ui, ui, char>;
   table = vector<uiT>table;
   int l_numChar = a_string.size();
   // Number of elements in lower triangle of n^2 table
   int l_numElem = l_numChar * (l_numChar + 1)/2;
   if(!l_numChar) return string();
   // Initialize table
   table l_table(l_numElem);
   int l_index = 0;
   // Initialize corner of (0,0)
   l_table[l_index] = make_tuple(1,l_index,a_string[0]);
   l_index++;
   // Fill in table row-wise
   for(int i = 1; i < l_numChar; ++i)
   {
      // Left most character in substring ending at i
      auto l_char = a_string[i];
      // Fill in base case of (i,i)
      l_table[l_index] = make_tuple(1,l_index,l_char);
      l_index++;
      // Fill in case of (i-1,i)
      if(l_char == a_string[i-1]) l_table[l_index] = make_tuple(2, l_index,l_char);
      else l_table[l_index] = make_tuple(1, l_index, l_char);
      l_index++;
      // Fill in substrings (i-2,i) to (0,i)
      for(int j = i-2; j >= 0; --j)
      {
         // Index for (j+1,i-1)
         int l_innerIndex = l_index - i - 2;
         // If beginning and ending charaters of substring match,
         // longest subpalindrome occurs using substring (j+1,i-1)
         if(l_char == a_string[j]) l_table[l_index] = make_tuple(get<0>(l_table[l_innerIndex]) + 2, l_innerIndex, l_char);
         / If not, longest subpalindrome is either (j,i-1) or (j+1,i)
         else {
            int l_maxIndex = get<0>(l_table[l_index-1]) < get<0>(l_table[l_innerIndex+1]) ? l_innerIndex+1 : l_index-1;
            l_table[l_index] = make_tuple(get<0>(l_table[l_maxIndex]), l_maxIndex, '\0');
         }
         l_index++;
      }
   }

   string l_resultString;

   // Traceback the final string. Note: the longest substring may not
   // be unique
   // Following parent pointers and collecting added characters gives
   // half of the palindrome
   l_index = l_numElem - 1;
   while(true) {
      int l_nextInd = get<1>(l_table[l_index]);
      char l_char = get<2>(l_table[l_index]);

      if(l_char != '\0') l_resultString += l_char;
      if(l_nextInd == l_index) break;

      l_index = l_nextInd;
   }
   // Other half of the palindrome is now added by mirroring the

   // l_resultString
   char l_beg = l_resultString.rbegin();
   if(get<0>(l_table[l_numElem-1]) % 2 == 1) l_beg++;
   l_resultString.append(string(l_beg, l_resultString.rend()));

   return l_resultString;
}
