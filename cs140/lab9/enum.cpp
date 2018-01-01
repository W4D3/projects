#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

class Enum{
    public:
        Enum(int length);
        void do_enumeration(int index, int ones);
    private:
        string s;
        int length;
};

/* Construct Enum with the length fromn the cmd line and 0's */
Enum::Enum(int l) {    
    length = l;
    s.resize(length, '0');
}

void Enum::do_enumeration(int index, int ones) {

    /* If the you have more ones than indicies of s, return*/
    if (ones > length-index) {
        return;
    }

    /* Base Case */
    if (index == length) {
        if (ones == 0) {
            cout << s << endl;
        } 
    } else {
            do_enumeration(index+1, ones);  // Index, Enumerate
        if (ones > 0){
            s[index] = '1'; // Put a one at the index of s
            do_enumeration(index+1, ones-1); // Index, Enumerate, Decrement ones
            s[index] = '0'; // Put a zero at the index of s 
        }
    
    }
}

int main(int argc, char **argv) {
    
    int length, ones;   /* Length of numbers, numbers of ones */
    Enum *ptr;          /* Ptr to Enum object */

    /* Check for proper usage */
    if (argc != 3) {
        fprintf(stderr, "usage: enum length ones \n");
        exit(1);
    }

    /* Transform the command line to integers */
    length = atoi(argv[1]);
    ones = atoi(argv[2]);

    /* Create a new Enum object */
    ptr = new Enum(length);
    
    /* Print out the string of numbers recursively */
    ptr->do_enumeration(0, ones);
    
    return 0;
}
