#include "incremental_inverse.h"

Incremental_Inverse::Incremental_Inverse(int rows, Galois_Field *G)
{
  int i;

  gf = G;
  Rows = rows;
  NCols = 0;
  Cols.clear();
  Cols.resize(rows);
  for (i = 0; i < rows; i++) Cols[i].resize(rows);
  Pivots.clear();
  Pivots.resize(rows);
  for (i = 0; i < rows; i++) Pivots[i] = i;
}

int Incremental_Inverse::Add_Col(vector <unsigned int> &col)
{
  int i, r, multiplier;

  if (NCols == Rows) return 0;

  if (Rows != col.size()) {
    cerr << "Error -- called Incremental_Inverse::Add_Col() on cols with multiple sizes\n";
    exit(1);
  }
  for (i = 0; i < Rows; i++) Cols[NCols][i] = col[i];
  
  for (r = 0; r < NCols; r++) {
    if (Cols[NCols][Pivots[r]] != 0) {
      multiplier = gf->Divide(Cols[NCols][Pivots[r]], Cols[r][Pivots[r]]);
      for (i = 0; i < Rows; i++) {
        Cols[NCols][i] ^= gf->Multiply(multiplier, Cols[r][i]);
      }
    }
  }
  for (i = 0; i < Rows && Cols[NCols][i] == 0; i++) ;
  if (i == Rows) return 0;
  for (i = NCols; i < Rows && Cols[NCols][Pivots[i]] == 0; i++) ;
  if (i != NCols) {
    r = Pivots[NCols];
    Pivots[NCols] = Pivots[i];
    Pivots[i] = r;
  }
  NCols++;
  return 1;
}

void Incremental_Inverse::Delete_Col()
{
  if (NCols == 0) {
    cerr << "Error -- called Incremental_Inverse::Delete_Col() on an empty matrix\n";
    exit(1);
  }
  NCols--;
}

void Incremental_Inverse::Print()
{
  int i, j;

  printf("II-Matrix:\n");
  for (i = 0; i < NCols; i++) {
    for (j = 0; j < Rows; j++) printf(" %5d", Cols[i][j]);
    printf("\n");
  }
  printf("Pivots:\n");
  for (i = 0; i < Rows; i++) printf(" %d", Pivots[i]);
  printf("\n");
}
