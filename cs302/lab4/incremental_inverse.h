#ifndef _LAB4_INCREMENTAL
#define _LAB4_INCREMENTAL
#include "galois_field.h"

class Incremental_Inverse {
  public:
    Incremental_Inverse(int rows, Galois_Field *gf);
    int Add_Col(vector <unsigned int> &col);
    void Delete_Col();
    void Print();   
  protected:
    Galois_Field *gf;
    vector <UIVec> Cols;
    vector <int> Pivots;
    int Rows;
    int NCols;
};
#endif
