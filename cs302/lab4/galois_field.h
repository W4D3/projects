#ifndef _LAB4_GALOIS
#define _LAB4_GALOIS
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef vector <unsigned int> UIVec;
class Galois_Field {
  public:
    Galois_Field(int w);
    unsigned int Multiply(unsigned int a, unsigned int b);
    unsigned int Divide(unsigned int a, unsigned int b);
    unsigned int Inverse(unsigned int a);
  protected:
    int W;
    vector <unsigned char> Mult_Table_8;
    vector <unsigned char> Div_Table_8;
    vector <unsigned short> Log_Table_16;
    vector <unsigned short> ILog_Table_16;
    vector <UIVec> Tables_32;
};
#endif
