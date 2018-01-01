#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.h"

typedef vector <int> IVec;

/*
   bitmatrix.cpp
   Mitchell Wade
   March 11, 2014
 
   This program allows the user to manipulate bit matrixes in a multitude of ways.
   You can change individual values, swap rows, change the bitmatrix into a pgm,
   etc. There are many methods that use for loops to access memory and there are
   also points to bitmatrixs and hashtable spots that also allow the user to access
   certain parts of memory. 
 */

/* Creates a bitmatrix of all 0's */
Bitmatrix::Bitmatrix(int rows, int cols)
{
    int i, j;

    //Check for bad input
    if ((rows <= 0) || (cols <= 0 )) {
        fprintf(stderr, "Bad matrix file\n");
        M.resize(1); M[0].resize(1), M[0][0] = '0';
    } else {
        
        //Initalize the values
        M.resize(rows);
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                M[i].push_back('0');
            }
        }
    }
}


int Bitmatrix::Rows()
{
    return M.size();
}

int Bitmatrix::Cols()
{
    return M[0].size();
}

/* Sets an individual value in the bitmatrix */
void Bitmatrix::Set(int row, int col, char val)
{
    if ((row < 0) || (col < 0)) {
        exit(0);
    } else if ((val == '0') || (val = '1')) {
        M[row][col] = val;
    } else if ((val == 0) || (val == 1)) {
        M[row][col] = val + '0';        //change ASCII value
    }
}
  
/* Returns a specified position of the bitmatrix */
char Bitmatrix::Val(int row, int col)
{
    if ((row < 0) || (col < 0)) {
        return -1;
    } else {
        return (M[row][col] - '0');     //change ASCII value
    }
}

/* Prints the bitmatrix */
void Bitmatrix::Print(int w) 
{
  int i, j;

  for (i = 0; i < M.size(); i++) {
    if (w > 0 && i != 0 && i%w == 0) printf("\n");
    if (w <= 0) {
      cout << M[i] << endl;
    } else {
      for (j = 0; j < M[i].size(); j++) {
        if (j % w == 0 && j != 0) printf(" ");
        printf("%c", M[i][j]);
      }
      cout << endl;
    }
  }
}

/* Writes the bitmatrix to a file */
void Bitmatrix::Write(string fn) 
{
    int i, j;
    string s;
    ofstream f;

    f.open(fn.c_str());
    if (f.fail()) { 
        perror(fn.c_str()); 
        M.resize(1); M[0].resize(1), M[0][0] = '0'; 
        return; 
    }

    for (i = 0; i < M.size(); i++) {
        if (i != 0) {
            f << "\n";
        }
        for (j = 0; j < M[0].size(); j++) {
            f << M[i][j];
        }
    }
    
    f << endl;
    f.close();
}

/* Swaps two specified rows of the bitmatrix */
void Bitmatrix::Swap_Rows(int r1, int r2)
{
    vector <string> tmp;

    if ((r1 < 0) || (r2 < 0)) {
        exit(0);
    } else {

        /* Swap function */
        tmp.push_back(M[r1]);
        M[r1] = M[r2];
        M[r2] = tmp[0];
    }
}

/* Adds add specified rows together and puts it in the r1 row */
void Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
    int i;
    unsigned char R1, R2;
    char sum;
    
    /* Changes ASCII values and sums the result of each position */
    for (i=0; i<M[0].size(); i++) {
        R1 = (M[r1][i] - '0');      
        R2 = (M[r2][i] - '0');
        
        sum = ((R1 ^ R2) + '0');
        
        M[r1][i] = sum;
    }
}

/* Reads a bitmatrix from a file */
Bitmatrix::Bitmatrix(string fn) 
{
  ifstream f;
  int i, j;
  string s, row;

  f.open(fn.c_str());
  if (f.fail()) { 
      perror(fn.c_str()); 
      M.resize(1); M[0].resize(1), M[0][0] = '0'; 
      return; 
  }

  while (getline(f, s)) {
      row.clear();
      for (i = 0; i < s.size(); i++) {
          if (s[i] == '0' || s[i] == '1') {
        row.push_back(s[i]);
      } else if (s[i] != ' ') {
        fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
        M.resize(1); M[0].resize(1), M[0][0] = '0'; 
        f.close();
        return;
      }
    }
    if (s.size() > 0 && M.size() > 0 && row.size() != M[0].size()) {
        fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
        M.resize(1); M[0].resize(1), M[0][0] = '0'; 
        f.close();
        return;
    }
    if (s.size() > 0) M.push_back(row);   
  }
  f.close();
}

/* Changes the current bitmatrix to a PGM file */
void Bitmatrix::PGM(string fn, int pixels, int border)
{
    int i, j, k, l;         // Iteration Variable
    int r, c, pb;           // Rows and Columns
    ofstream f;             //PGM Output file
    vector <IVec> pgm;      // PGM from Bitmatrix and Borders
    
    r = Rows() * pixels + (Rows()+1) * border;
    c = Cols() * pixels + (Cols()+1) * border;
    pb = pixels + border;
    
    // Resize PGM
    pgm.resize(r);
    for (i = 0; i < r; i++) {
        pgm[i].resize(c, 0);
    }
    
    // Open the PGM file
    f.open(fn.c_str());
    
    // Write PGM File Specifications
    f << "P2\n" << c << " " << r << "\n" << "255\n";
    
    // Put the pixel value into the pgm vector
    for (i = 0; i < M.size(); i++) {
        for (j = 0; j < M[0].size(); j++) {
            for (k = 0; k < pixels; k++) {
                for (l = 0; l < pixels; l++) {
                    if (M[i][j] == '0') {
                        pgm[border + i*(pb) + k][border + j*(pb) + l] = 255;
                    } else { 
                        pgm[border + i*(pb) + k][border + j*(pb) + l] = 100;
                    }
                }
            }
        }
    }

    //Output
    for (i = 0; i < pgm.size(); i++) {
        for (j = 0; j < pgm[0].size(); j++) {
            f << pgm[i][j] << " ";
        }
    }

    f.close();
}

/* Copies a bitmatrix */
Bitmatrix *Bitmatrix::Copy()
{
    int i, j;
    Bitmatrix *copy;
    
    /* Create copy */
    copy = new Bitmatrix(Rows(), Cols());
    
    /* Initalize elements from bitmatrix M */
    for (i = 0; i < Rows(); i++) {
        for (j = 0; j < Cols(); j++) { 
            copy->Set(i, j, M[i][j]);
        }
    }

    return copy;
}


BM_Hash::BM_Hash(int size)
{
    table.resize(size);
}

/* DJB Hash function from lecture notes */
unsigned int djb_hash(string &s)
{
    int i;
    unsigned int h;
    
    h = 5381;
    
    for (i = 0; i < s.size(); i++) {
        h = (h << 5) + h + s[i];
    }
    return h;
}

/* Stores the bitmatrix in the hash table */
void BM_Hash::Store(string &key, Bitmatrix *bm)
{
    int i;
    int j = 0;
    unsigned int location;
    
    location = djb_hash(key)%table.size();
    
    for (i = 0; i < table[location].size(); i++) {
        if (key  == table[location].at(i) -> key) {
            table[location][i]-> bm = bm; 
            j = 1;
            } 
        }  

    /* Creates a new bitmatrix for the hash table if  */
    /* the bitmatrix doesn't already exist in the table */
    HTE *hte;
    if (j != 1){
        hte = new HTE(); 
        hte-> key = key; 
        hte-> bm = bm;
        table[location].push_back(hte);
    }
}
  
/* Outputs a specified bitmatrix if the hash table contains it */
Bitmatrix *BM_Hash::Recall(string &key)
{
    int i;
    int j = 0;
    int k = 0;
    int location;

    location = djb_hash(key)%table.size();

    /* If found set j to TRUE and k to the spot in the table */
    for (i = 0; i < table[location].size(); i++) {
        if (key  == table[location].at(i) -> key) {
            j = 1;
            k = i;
        }
    }

    /* Output */
    if (j == 1) {
        return (table[location].at(k) -> bm);
    } else 
        return NULL;
}

/* Outputs all of the hash table values */
HTVec BM_Hash::All()
{
    int i, j;
    HTVec rv;

    for (i = 0; i < table.size(); i++) {
        for (j = 0; j < table[i].size(); j++) {
            rv.push_back(table[i].at(j));
        }
    }
    return rv;
}

/* Sums two bitmatrixes */
Bitmatrix *Sum(Bitmatrix *m1, Bitmatrix *m2)
{
    int i, j;
    int m1_Element = 0;
    int m2_Element = 0;
    int sum = 0;
    Bitmatrix* sumMatrix;

    sumMatrix = new Bitmatrix(m1->Rows(), m1->Cols());

    if (m1->Rows() != m2->Rows()) {
        return NULL;
    } else if (m1->Cols() != m2->Cols()) {
        return NULL;
    } else {
        for (i = 0; i < m1->Rows(); i++) {
            for (j = 0; j < m1->Cols(); j++) {
                m1_Element = m1->Val(i, j);             //1st spot 
                m2_Element = m2->Val(i, j);             //2nd spot
                sum = (m1_Element^m2_Element + '0');    //sum them
                sumMatrix->Set(i, j, sum);              //initalize
                }
        }

        return sumMatrix;
    }
}

Bitmatrix *Product(Bitmatrix *m1, Bitmatrix *m2)
{
    int i, j, k;
    int m1_Element = 0;
    int m2_Element = 0;
    int sum = 0;
    Bitmatrix* productMatrix;
    
    productMatrix = new Bitmatrix(m1->Rows(), m2->Cols());
    
    if (m1->Cols() != m2->Rows()){
        return NULL;
    } else {
        for (i = 0; i < m1->Rows(); i++) {
            for (j = 0; j < m2->Cols(); j++) {
                for (k = 0; k < m1->Cols(); k++) {
                    m1_Element = m1->Val(i, k);         //1st spot
                    m2_Element = m2->Val(k, j);         //2nd spot
                    sum += (m1_Element*m2_Element);     //sum them
                }
                sum = ((sum%2) + '0');                  //find the new product
                productMatrix->Set(i, j, sum);          //initalize
                sum = 0;                                //clear the sum
            }
        }
        
        return productMatrix;
    }
}

// Only return &rows specified from Bitmatrix 
Bitmatrix *Sub_Matrix(Bitmatrix *m, vector <int> &rows)
{
    int i, j;
    char temp;
    Bitmatrix* subMatrix;
    
    subMatrix = new Bitmatrix(rows.size(), m->Cols());

    if ((rows.size() == 0) || (rows[0] < 0)) {
        return NULL;
    } else {
        for (i = 0; i < rows.size(); i++) {
            for (j = 0; j < m->Cols(); j++) {
                temp = m->Val(rows[i], j);                  //find row
                subMatrix->Set(i, j, (temp + '0'));         //initalize new matrix
            }
        }

        return subMatrix;
        }
}

Bitmatrix *Inverse(Bitmatrix *m)
{
    /*
    int i, j, k;
    int r = m->Rows();
    int c = m->Cols();
    Bitmatrix *Mcopy;
    Bitmatrix *Inv;
    
    Mcopy = new Bitmatrix(m->Rows(), m->Cols());
    Inv = new Bitmatrix(m->Rows(), m->Cols());

    for(i = 0; i <= r; i++) { 
        for(i = 0;i <= c; i++) {
            if (m->Val(i, j) != 1) {
                i++;
            } else {
                //Swap_Rows(i, j);
            } else {
                //Matrix not invertible
            }
        }
    }

    return Inv;
    */
}
