#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

/* moonglow.cpp
   Mitchell Wade
   February 1, 2014
   
   This program deciphers a text file by organizing a students name and their
   grades and outputs that information.
 
 */

using namespace std;

int main(){

    double score = 0;          /* The value of the current score */
    double sumOfScores = 0;      /* The sum of the  scores */
    double numScores = 0;        /* The number of scores following an average */
    double finalScore = 0;       /* The final value of the students score */
    double average = 0;          /* The average number of the scores */
    string input, name;         /* The input and name of the student */
    double errorCheck = 0;

    while (!cin.eof()){

        cin >> score;
        if (errorCheck != score){
            finalScore+=score;
        }
        errorCheck = score;
        
        if (cin.fail()){
            cin.clear();
            cin >>input;
        }
        
        if (input == "NAME"){
            cin >> input;
            name = input;
        } else if (input == "AVERAGE"){
            while(cin >> score){
                sumOfScores+=score;
                numScores++;
            }

        if (numScores >= 1){
        average = (sumOfScores/numScores);
        finalScore+=average;
        sumOfScores = 0;
        numScores = 0;
        }
        }

    }
    
    cout << name << " " << finalScore <<endl;
    
    return 0;
}
