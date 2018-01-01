#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include "galois_field.h"
#include "incremental_inverse.h"

using namespace std;

// is_jls.cpp
// Mitchell Wade
// October 2, 2014
//
// This program takes a line of input from the command line
// and determines if the data can be recovered after various
// disk and sector failures have happened. It uses enumeration
// to determine all of the possible ways the disks and sectors
// can fail and then depending upon if the information is
// invertible or not it will tell you if it is recoverable or
// not.

typedef vector <unsigned int> UIVec;

class JLS {
    public:
        unsigned int n, m, s, r, w;
        vector <UIVec> pcm;
        int GF_Pow(Galois_Field* gf, int v, int x);
        Galois_Field *gf;
        JLS *jls;
        void GenDiskFails(int index, int remainding);
        void GenSectorFails(int index, int remainding);
        string str;
        Incremental_Inverse *inc;
};

// Power function for Galois Fields
int JLS::GF_Pow(Galois_Field* gf, int v, int x) {
    
    int i, rv = 1;

    for (i = 0; i < x; i++) {

        rv = gf->Multiply(rv, v);
    }

    return rv;
}

// Enumerates sector failures
void JLS::GenSectorFails(int index, int remaining) {
    
    int i;

    // If there are no disks left, return
    if (remaining == 0) {
        return;
    }

    // If the disk we are at is greater than the number of disks, return
    if (remaining > r*n - index) return;

    // If its already down don't take the sector down again
    if (str[index] == 'D') {
        GenSectorFails(index+1, remaining);
        return;
    }

    // It failed, set the element in the string to S
    str[index] = 'S';

    // If it is not invertible, print No: string
    if (inc->Add_Col(pcm[index]) == 0) {
        printf("No: %s\n", str.c_str());
        exit(1);
    }

    // If it didn't fail set it back to U, go back
    GenSectorFails(index+1, remaining-1);
    str[index] = 'U';
    // Keep going, delete the collumn
    inc->Delete_Col();

    // Enumerate
    GenSectorFails(index+1, remaining);
}

// Enumerates disk failures
void JLS::GenDiskFails(int index, int remaining) {

    int i;

    // If there are no disks left, return
    if (remaining == 0) {
        GenSectorFails(0, s);
        return;
    }

    // If the disk we are at is greater than the number of disks, return
    if (remaining > n - index) return;

    // It failed
    for (i = 0; i < r; i++) {
        str[n*i+index] = 'D';

        // If it is not invertible, print No: string
        if (inc->Add_Col(pcm[n*i+index]) == 0) {
            printf("No: %s\n", str.c_str());
            exit(1);
        }
    }

    // If it didn't fail set it back to U, go back 
    GenDiskFails(index+1, remaining-1);
    
    for (i = 0; i < r; i++) {
        str[n*i+index] = 'U';

        // Keep going, delete the collumn
        inc->Delete_Col();
    }

    // Enumerate
    GenDiskFails(index+1, remaining);
}

int main(int argc, char **argv) {

    int i = 0, j = 0, x = 0, k = 0;
    unsigned int n = 0, m = 0, s = 0, r = 0, w = 0, a = 0;
    vector <UIVec> pcm;
    vector <int> A;
    JLS *jls;
    Galois_Field *gf;
    Incremental_Inverse *inc;

    jls = new JLS;
    
    // Read in part of the command line
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    s = atoi(argv[3]);
    r = atoi(argv[4]);
    w = atoi(argv[5]);
    
    // Store the command line values in the class variables
    jls->n = n;
    jls->m = m;
    jls->s = s;
    jls->r = r;
    jls->w = w;
    
    // Caclulate the remaining number of command line values
    a = m+s;

    // Initalize the string
    jls->str.resize(n*r, 'U');

    // Read in the m+s command line elements
    for(int i = 6; i < argc; i++) {
        A.push_back(atoi(argv[i]));
    }

    gf = new Galois_Field(w);
    
    // Resize the outside vector to disks * words
    jls->pcm.resize(n*r); //pcm.resize(n*r);
    for (i = 0; i < jls->pcm.size(); i++ ) {
        // Resize the inside vector to disk failures * words + sector failures
        jls->pcm[i].resize(m*r+s, 0);
    }

    // Creates some of the PCM elements
    for (x = 0; x < m*r; x++) {
        i = x%r;
        k = x/r;

        for (j = 0; j < n; j++) {
            jls->pcm[n*i+j][x] = jls->GF_Pow(gf, A[k], n*i+j); 
        }
    }

    // Creates the last two rows of the PCM
    for (i = 0; i < s; i++) {
        for (j = 0; j < n*r; j++) {
            jls->pcm[j][m*r+i] = jls->GF_Pow(gf, A[m+i], j);
        }
    }
    
    // Initialize the pointer
    inc = new Incremental_Inverse(m*r+s, gf);

    // Enumerate all failure scenarios
    jls->inc = inc;
    jls->GenDiskFails(0, m);

    printf("OK\n");

    return 0;
}
