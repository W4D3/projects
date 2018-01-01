#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

int main() {
   ifstream is;;
   ofstream os;
   int averageStableStates = 0;
   float averageUnstableProb = 0;
   int i = 0, j = 0;
   int stableCount = 0, unstableCount = 0;
   int curStable = 0;
   float curUnstable = 0;
   string str;
   FILE* csv, csv2;
   
   csv = fopen("probabilities.csv", "r+");
   csv2 = fopen("averages.csv", "w+");

   while(getline(csv, str, ',') {
      
   }

   fclose(csv);
   fclose(csv2);
   return 0;
}
