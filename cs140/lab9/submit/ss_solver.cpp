#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>

using namespace std;

typedef vector <string> svec;

/*
   Mitchell Wade
   ss_solver.cpp
   April 24, 2014

   This program allows a user to play the game shape shifter like crafted in
   NeoPets. However, this part of the program is the solver application. It
   will take on the command line the inital grid of 1's or 0's and will then
   read in the shapes that it will use to change the grid from standard input
   which will be from a file. Then the program will output the solution.

*/

class Shape_Shifter {
	public:
		Shape_Shifter(svec board, vector <svec> shapes);
		bool Shape_Shifter_Enum(int shape);
		void Apply_Shape(int row, int col, int shape);
        void Print();
        bool isCorrect();
	protected:
        vector <int> iResult;
        vector <int> jResult;
		svec grid;
		vector <svec> shapes;
};

/* Constructor */
Shape_Shifter::Shape_Shifter(svec board, vector <svec> shapes) {
    this->grid = board;
    this->shapes = shapes;
}

/* Print */
void Shape_Shifter::Print() {

    int i, j;

    /* Reverse the steps to solution */
    //reverse(shapes.begin(), shapes.end());
    reverse(iResult.begin(), iResult.end());
    reverse(jResult.begin(), jResult.end());

    /* Read through the shapes vector */
    for (i = 0; i< shapes.size(); i++) {
        for (j=0; j<shapes[i].size(); j++) {

            /* Print out the shape */
            cout << shapes[i][j] << " ";
        }
    
        /* Print out the coordinates */
        cout << iResult[i] << " " << jResult[i] <<endl;
    }
}

/* Finds the result of shape shifter */
bool Shape_Shifter::Shape_Shifter_Enum(int shape) {

    //printf("%*sCalled at shape index = %d\n", shape*2, "", shape);
    int i, j;

    /* If all shapes have been used check to see if its correct */
    if (shape == shapes.size()) {
        if (isCorrect() == true) {
            //printf("%*sCorrect Grid!\n", shape*2+2, "");
            return true;
        }
        //
         //printf("%*sInorrect Grid.\n", shape*2+2, "");
        return false;
    } else {

        /* Check to see if any shapes hasn't been used */
        if (shape < shapes.size()) {
            
            /* Read through the grid */
            for (i=0; i<grid.size() - shapes[shape].size() + 1; i++) {
                for (j=0; j<grid[0].size() - shapes[shape][0].size() + 1; j++) {
                    //printf("%*sApplying shape at (%d, %d)\n", shape*2+2, "", i, j);
                    /* First Attempt */
                    Apply_Shape(i,j, shape);

                    /* If correct, save the indicies */
                    if (Shape_Shifter_Enum(shape+1) == true) {
                        iResult.push_back(i);
                        jResult.push_back(j);
                        return true;
                    }

                    /* Undo the First Attempt */
                    Apply_Shape(i, j, shape);
                }
            }
            
        }
    }
    return false;
}

void Shape_Shifter::Apply_Shape(int row, int col, int shape) {

    int i, j;

    /* Read through the shapes vector of svec  */
    for (i=0; i<shapes[shape].size(); i++) {
        for (j=0; j<shapes[shape][0].size(); j++) {

            /* Change the corresponding spot */
            if (shapes[shape][i][j] == '1') {
                if (grid[row+i][col+j] == '0' ) { 
                    grid[row+i][col+j] = '1';
                } else 
                    grid[row+i][col+j] = '0';
            }
        }
    }
}

/* Check to see if the grid is correct */
bool Shape_Shifter::isCorrect() {

    int i, j;

    /* Read through the grid */
    for (i=0; i<grid.size(); i++) {
        for (j=0; j<grid[0].size(); j++) {

            /* Return if grid has any 0's */
            if (grid[i][j] != '1') return false;
        }
    }

    // Return if grid is all 1's */
    return true;
}

int main(int argc, char **argv) {

    int i;
    Shape_Shifter *ptr;
    string s, linetmp, line2tmp;
    vector <svec> shapes;
    svec grid;
    svec tmp;
    istringstream iss;

    /* Read in the grid */
    for (i=1; i<=argc-1; i++) {
        grid.push_back(argv[i]);
    }

    /* Read in the shapes */
    while(getline(cin, linetmp)) {
        iss.clear();
        tmp.clear();
        iss.str(linetmp);  //grab the next shape

        /* Check for shapes on multiple lines */
        while(iss >> line2tmp) { 
        tmp.push_back(line2tmp);
        }
        shapes.push_back(tmp);
    }

    /* Create an instance of Shape_Shifter */
    ptr = new Shape_Shifter(grid, shapes);
    
    /* Call the function recursively and print solution */
    if(ptr->Shape_Shifter_Enum(0) == true) {
        ptr->Print();
    }

    return 0;
}
