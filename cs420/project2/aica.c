// aica.c
// Mitchell Wade
// 2/28/2016
// This program creates an activation/inhibition cellular automaton for
// a 30x30 grid of cells. It will then update the cells, converge the cells
// to a proper state, and then create a csv file for data analysis.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// GLOBAL VARIABLES
int J1, J2, R1, R2, h;
int grid[30][30];
double m1[15];
double m2[15];
double m3[15];
// entropy variable
// correlation variable
// average of runs (4)

// DISTANCE FUNCTION
int calculateDistance(int i1, int j1, int i2, int j2) {
   int rij = 0;
   int x = 0;
   int y = 0;

   x = abs(i1 - j1);
   y = abs(i2 - j2);

   if (x > 15) {
      x = 30 - x;
   }
   
   if (y > 15) {
      y = 30 - y;
   }
   
   rij = x + y;

   return rij;
}

// CONVERGE FUNCTION
void gridUpdate(h, J1, J2, R1, R2) {

   int i = 0;
   int j = 0;
   int updateGrid[30][30];
   int num = 0;
   int sum = 0;
   //int si = 0;
   int updatedFlag = 0;
   int count = 0;
   int nearbySum = 0;
   int fartherSum = 0;

   // Initialize the update grid
   for(i = 0; i < 30; i++) {
      for(j = 0; j < 30; j++) {
         updateGrid[i][j] = 0;
      }
   }
   
   while(count != 900) {
      while(updateGrid[num][j] != 1) {
      
         srand(time(NULL));
         num = rand()%30;
         updateGrid[num][j] = 1;
      
         for(i = 0; i < 900; i++) {
            for(j = 0; j < i; j++) {
               if (i == num) {
                  break;
               } else {
                  tmp = calculateDistance(i, j, i, j);
                  if (tmp < R1) {
                     nearbySum += tmp;
                  } else if (tmp >= R1 && tmp < R2) {
                     fatherSum += tmp;
                  }
               }
            }
         }
      }
      
      while(updateGrid[i][num] 
         for(i = 0; i < 30; i++) {
            for(j = 0; j < 30; j++) {
               if (j == num) {
                  break;
               } else {
                  tmp = calculateDistance;
                  if (tmp < R1) {
                     nearbySum += tmp;
                  } else if (tmp >= R1 && tmp < R2) {
                     fatherSum += tmp;
                  }
               }
            }
         }

      count++;
   }
      // Effect of nearby cells
      //
      /*h + J1
         if (grid[i][j] < R1) {
            sum += updateGrid
         }
*/
      // Effect of father away cells
   }
}

// CREATE GRID
void createGrid() {
   
   int i = 0, j = 0;
   int num = 0;

   srand(time(NULL));

   // Randomly initialize the grid
   for (i = 0; i < 30; i++) {
      for (j = 0; j < 30; j++) {
         num = rand()%2;
         //num = ran()%2+0;
         if (num == 0) {
            grid[i][j] = -1;
         } else {
            grid[i][j] = 1;
            //grid[i][j] = num;
         }
      }
   }
}

// MAIN PROGRAM TO CREATE SIMULATION
int main(int argc, char *argv[]) {
   
   int i = 0, j = 0;
   int state[30][30];
   int R1 = 0;
   int R2 = 0;
   int J1 = 0;
   int J2 = 0;
   int h = 0;
   int ID = 0;
   char hBuff[100];

   // Read in cmd line
   if(argc != 7 ){
      printf("Usage: ./aica J1 J2 R1 R2 h ID\n");
      exit(0);
   } else {
      J1 = atoi(argv[1]);
      J2 = atoi(argv[2]);
      R1 = atoi(argv[3]);
      R2 = atoi(argv[4]);
      h = atoi(argv[5]);
      ID = atoi(argv[6]);
   }

   createGrid();
   gridUpdate();

   // check for grid being all 0's or all 1's

   return 0;
}
