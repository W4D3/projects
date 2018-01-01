#include <iostream>
#include "product.h"

using namespace std;

/*
   product.cpp
   Mitchell Wade
   March 28, 2014

   This program allows a user to simulate his odds when playing keno.
   The user can manipulate a vector by  either multiplying  factorials,
   dividing factorials, and can calculate the sum of the product.
*/

/* Switch the numerator and denominator elements within the vector */
void Product::Invert() {

    vector <int> tmp;

    tmp = numerator;
    numerator = denominator;
    denominator = tmp;
}

/* Set each location in the vector to # n */
void Product::Multiply_Number(int n) {

    //Resize the vectors 
    if (numerator.size() <= n) {
        numerator.resize(n+1);
        denominator.resize(n+1);
    }

    //Add a 1 or take a 1 away
    if (denominator[n] > 0) {
        denominator[n]--;
    } else numerator[n]++;
}

/* Set each location in the vector to # n */
void Product::Divide_Number(int n) {

    //Resize the vectors
    if (denominator.size() <= n) {
        denominator.resize(n+1);
        numerator.resize(n+1);
    }

    //Add a 1 or take a 1 away
    if (numerator[n] > 0) {
        numerator[n]--;
    } else denominator[n]++;
}

/* Call Multiply_Number and set each # up to n */
void Product::Multiply_Factorial(int n) {

    int i;

    for (i=2; i<=n; i++) { 
        Multiply_Number(i);
    }
}

/* Call Multiply_Number and set each # up to n */
void Product::Divide_Factorial(int n) {

    int i;

    for (i=2; i<=n; i++) { 
        Divide_Number(i);
    }
}

/* Use the class to change each position calling Mul. or Div. */
void Product::Multiply_Binom(int n, int k) {
    
    //((n!)/((k!)(n-k!)))
    Multiply_Factorial(n);
    Divide_Factorial(k);
    Divide_Factorial(n-k);
}

/* Use the class to change each position calling Mul. or Div. */
void Product::Divide_Binom(int n, int k) {
    
    //((n!)/((k!)(n-k!)))
    Divide_Factorial(n);
    Multiply_Factorial(k);
    Multiply_Factorial(n-k);
}

/* Clear all elements in the vectors */
void Product::Clear() {
    
    numerator.resize(0);
    denominator.resize(0);
}

/* Print out the vectors as factorials  */
void Product::Print() {

    int i, j;
    int flag = 0;

    for (i=2; i<numerator.size(); i++) {
        for (j=1; j<=numerator[i]; j++) {
                
                //If numerator has printed out a number add 
                //a * between the next number
                if (flag != 0) {
                    cout << " * ";
                }
                cout << i;
                flag++;
        }
    }

    //Check to see if the numerator is bigger than 1
    if (flag == 0) {
        cout << "1";
    }
    
    for (i=2; i<denominator.size(); i++) {
        for (j=1; j<=denominator[i]; j++) {
            cout << " / " << i;
        }
    }

    cout << endl;
}

/* Add all of the elements of the vector and print the sum */
double Product::Calculate_Product() {

    int i, j;
    double prod = 1;

    for (i=2; i<numerator.size(); i++) {
        for (j=1; j<=numerator[i]; j++) {
            prod *= i;
        }
    }

    for (i=2; i<denominator.size(); i++) {
        for (j=1; j<=denominator[i]; j++) {
            prod /= i;
        }
    }

    return prod;
}
