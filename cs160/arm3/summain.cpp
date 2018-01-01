/* ==================================================================
 *
 * CS 160 (Gregor) -- arm3: Logarithmic reduction based summing of
 *                          elements in an array 
 *
 * summain.cpp
 *
 * ================================================================== */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef unsigned int uint;
extern "C" uint sumR(uint *, uint);

uint sumH(uint *x, uint N)
{
	uint i, h[256];

	for (i=0; i<256; i++)
	  h[i] = 0;

	for (i=0; i<N; i++)
	  h[x[i]]++;

	uint sum= 0;
	for (i=0; i<256; i++)
	  sum += i*h[i];
	
	return sum;
}

int main(int argc, char *argv[])
{
    srand(time(0));

    int N = 10;
    if (argc > 1) N = atoi(argv[1]);

    uint i, x[N];
    for (i=0; i<N; i++)
      x[i] = rand() & 0xff;

	uint sum_hist = sumH(x, (uint)N);
    uint sum_loop = sumR(x, (uint)N);
   
    cout << sum_hist << " " << sum_loop << endl;
}
