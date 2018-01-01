#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int main() {

   int i, j, k, m, p, pat;      // Iteration Variables
   int bipolar = 0;             // Random number (-1 or 1)
   int count = 0;               // Used when imprinting the neural net
   float total = 0;             // Used when computing neuron weights
   int pattern[50][100];        // Pattern array
   float weights[100][100];     // Weight array
   int net[100];                // Neural Net
   float h[100];                // New state value for each nueron
   float nextState[100];        // Next state value for each nueron
   int stableStates[50];        // Counts the number of stable states for each p
   float stableProb[50];        // Probability of stable imprints for each p
   float unstableProb[50];      // Probability of unstable imprints for each p
   FILE *csv;                   // .csv file for generating graphs of data
   float basins[50];            // Used for calculating each patterns basin
   int permutation[100];        // Used for generating a random array [1-100]
   int permutationFlags[100];   // Used for generating a random number [1-100]
   
   // Initialize stable states
   for(i=0; i<50; i++) {
      stableProb[i] = 0;
      unstableProb[i] = 0;
      stableStates[i] = 0;
   }
   
   //Initalize random number generation variables
   for(i=0; i<100; i++) {
      basins[i] = 0.0;           // 0 = unstable,
      permutationFlags[i] = 0;  // 0 = not filled, 1 = filled
   }

   // Initialize all elements of vector to -1 or 1
   srand(time(NULL));
   for(i=0; i<50; i++) {
      for(j=0; j<100; j++) {
         bipolar = rand() % 2;
         if (bipolar == 0) {
            pattern[i][j] = -1;
         } else {
            pattern[i][j] = 1;
         }
      }
   }

/*
   for(p=0; p<50;p++) {
      // Imprint patterns 1 through p by updating all of the weight vectors
      for(i=0; i<100; i++) {
         for(j=0; j<100; j++) {
            if(i!=j) {
               total = 0;
               for(k=0; k<p+1; k++) {
                  total += pattern[k][i] * pattern[k][j];
               }
               weights[i][j] = (total/100.0);
            } else if (i==j) {
               weights[i][j] = 0;
            }
         }
      }

      for(pat=0; pat<p+1; pat++) {
         // Imprint the first p patterns on a Hopfield net
         for(j=0; j<100; j++) {
            net[j] = pattern[pat][j]; // ...set it the pattern we are at
         }

         // Compute the new state value for each p patterns (local field)
         for(i=0; i<100; i++) { // for each 100 neurons
            total = 0;
            for(j=0; j<100; j++) {
               total += weights[i][j]*net[j];
            }
            h[i] = total; // new state value

            // Determine the next state of the current neuron
            if(h[i] < 0) {
               nextState[i] = -1;
            } else{
               nextState[i] = 1;
            }
         }

         // Compare the neuron's new state
         bool changed = 0;
         for(m=0; m<100; m++) {
            if(net[m] != nextState[m]) {
               changed = 1; //UNSTABLE
            }
         }

         // Compute probabilities of stable and unstable states
         if (changed == 0) {
            stableStates[p] += 1.0;
            basin[p] = 0.0
         } else {
            int permFlags[100]
            while (total != 100) {
               bool flagged = 1;
               permutation[100] = rand()%+1;
            }
         }
   }

   //Write data to a .csv file
   csv = fopen("probabilities.csv", "a+");
   if(csv == NULL) {
      printf("Error: Cannot open .csv file\n");
      exit(1);
   }

   fprintf(csv, "p, #-stable, #-unstable \n");
   for(p=0; p<50; p++) {
      stableProb[p] = stableStates[p]/(p+1.0);
      unstableProb[p] = 1 - stableProb[p];
      fprintf(csv, "%d, %d, %5.2f\n\n", p+1, stableStates[p], unstableProb[p]);
   }

   fclose(csv);
*/
   return 0;
}
