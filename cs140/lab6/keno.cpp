#include <iostream>
#include <cstdio>
#include "product.h"

using namespace std;

/*
   keno.cpp
   Mitchell Wade
   March 28, 2014

   This program allows a user to simulate keno bets. The user is
   asked to input the bet (money spent) and p (the number of balls
   picked). The program then uses the keno algorithm to calculate
   the probability of the bet and the expected return on investment.
   This information is displayed to the user along with the normalized
   representation of the probability.

*/

int main() {

    Product o;  /* How to access functions of product */
    double bet; /* Money spent */
    double c, p; /* Ball chosen by user , ball picked by the house */
    double prob; /* Probability of pick to be right*/
    double pay; /* Payment to play the game */
    double expReturn; /* ROI */
    double sum = 0; /* Sum of probabilities */

    cin >> bet >> p;
    
    printf("Bet: %.2lf\n", bet);
    printf("Balls Picked: %.0lf\n", p);

    while (cin >> c >> pay) {

        //Clear the functions below
        o.Clear();
        
        //Calculate the probability of bet
        o.Multiply_Binom(80-p, 20-c);
        o.Multiply_Binom(p,c);
        o.Divide_Binom(80, 20);
        prob = o.Calculate_Product();

        //Calculate the expected ROI
        expReturn = prob * pay;
        
        cout << "  Probability of catching " 
             << c 
             << " of " 
             << p 
             << ": " 
             << prob 
             << " -- " 
             << "Expected return: " 
             << expReturn 
             <<endl;

        sum += expReturn;  
    }

    printf("Your return per bet: %.2lf\n", sum-bet);
    printf("Normalized: %.2lf\n", (sum-bet)/bet);
}
