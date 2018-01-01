#include <iostream>
#include <cstdlib>

using namespace std;

/* gold.cpp
   Mitchell Wade
   January 27, 2014

    This program reads a map of standard input and prints the total of gold
    on the map.

 */

int main()
{
    char c;
    int i, j, k;                                     /* The value of iteration  */
    int temp;                                        /* The temporary gold value */
    int sum = 0;                                     /* The running sum of gold */
    string input;                                    /* The input string */
    string output = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";    /* String to attribute gold value to A-Z  */

    while (cin >> input){        
        for(i=0; i<input.size();i++){
                char c = input[i];
              
                /* Check for uppercase letters */
                if (isupper(c)){

                    /* Distinguish gold amount and add the gold */
                    for(j=0; j<output.size(); j++){
                        if (c  == output[j]){
                            k= j+1;
                            sum+=k;
                        }
                    }
                }
        }
    }

    /* Output the gold amount */

    cout << sum <<endl;

    return 0;
}
