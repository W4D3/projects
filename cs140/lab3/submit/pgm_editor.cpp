#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

typedef vector <int> IVec;

/*
   
   pgm_editor.cpp
   Mitchell Wade
   February 18, 2014

   This program allows a user to edit and create pgm files. More specifically,
   the user can either create a pgm under the constrants of one pixel value,
   flip a pgm file clockwise or counterclockwise, add a border or padding
   around a pgm file, and they can also panel a pgm file which is when you
   create multiple pictures of the same picture within the file.

*/

/* Outputs the pgm file */
void pgm_write(vector <IVec> p){

    int i, j, r, c;     /* Iteration variables */
    int k = 0;          /* The running sum of pixels */
    r = p.size();       /* The number of rows */
    c = p[0].size();    /* The number of columns */

    printf("P2\n%d %d\n255\n", c, r);

    /* Resize the vector p and add newlines after printing 20 pixels */
    for (i=0; i<p.size(); i++){
        for (j=0; j<p[i].size(); j++){
    
        if (k==20){
            printf("\n");
            k=1;
        } else {
            k++;
        }
            printf("%4d", p[i][j]);
        }
    }

    cout <<endl;
}

/* Creates a pgm file */
vector <IVec> pgm_create(int r, int c, int pv){
    
    vector <IVec> p;    /* The created vector */
    int i, j;           /* Iteration variables */
    
    /* Resize the vector p and add pixel values of pv */
    p.resize(r);
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            p[i].push_back(pv);
        }
    }

    return p;
}

/* Rotates a pgm file clockwise */
void pgm_cw(vector <IVec> &p){
    
    int i, j;               /* Iteration Variables */
    int r = p.size();       /* The number of rows */
    int c = p[0].size();    /* The number of columns */
    vector <IVec> pgm_cw2;  /* A vector turned clockwise */
    
    /* Resize the vector */
    pgm_cw2.resize(c);
    for (i=0; i<c; i++){
        pgm_cw2[i].resize(r);
    }

    /* Locate the pixel value and copy a new location into the vector */
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
                pgm_cw2[j][r-1-i] = p[i][j];
        }
    }

    p = pgm_cw2;

}

void pgm_ccw(vector <IVec> &p){
    
    int i, j;               /* Iteration Variables */
    int r = p.size();       /* The number of rows */
    int c = p[0].size();    /* The number of columns */
    vector <IVec> pgm_ccw2; /* The vector turned counterclockwise */
    
    /* Resize the vector */
    pgm_ccw2.resize(c);
    for (i=0; i<c; i++){
        pgm_ccw2[i].resize(r);
    }

    /* Locate the pixel value and copy a new location into the new vector */
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            pgm_ccw2[c-j-1][i] = p[i][j];
        }
    }

    p = pgm_ccw2;
}

/* Pad the pixels by adding w pixels around p */
void pgm_pad(vector <IVec> &p, int w, int pv){

   int i, j;                /* Iteration Variables*/
   int r = p.size();        /* The number of rows */
   int c = p[0].size();     /* The number of columns */
   int wr = r+(2*w);        /* The padded rows */
   int wc = c+(2*w);        /* The padded collumns */
   vector <IVec> pad;       /* The padded vector */

   /* Resize the vector */
   pad.resize(wr);
   for (i=0; i < wr; i++){
       pad[i].resize(wc);
       }
   
   /* Add the pixel value around the vector */
   for (i=0; i<wr; i++){
       for (j=0; j<wc; j++){
           if ((w<=i) && (i<(p.size()+w)) && (w<=j) && (j<(p[0].size()+w)))
                   pad[i][j]=p[i-w][j-w];
           else pad[i][j] = pv;
       }
   }

   p = pad;
}

/* This changes p so that it has r*c copies of the PGM file */ 
void pgm_panel(vector <IVec> &p, int r, int c){

    int i, j;                   /* Iteration Variables */
    int rows = p.size()*r;      /* The number of rows */
    int cols = p[0].size()*c;   /* The number of columns */
    vector <IVec> panel;        /* The vector that is panneled */

   /* Resize the vector */
    panel.resize(rows);
    for (i=0; i<rows; i++){
        panel[i].resize(cols);
    }
    /* Put the picture in each element of the vector */
    for (i=0; i<rows; i++){
        for (j=0; j<cols; j++){
            panel[i][j] = p[i%p.size()][j%p[0].size()];
        }
    }

    p = panel;

}

/* This changes p so that it has a subset of the original picture */
void pgm_crop(vector <IVec> &p, int r, int c, int rows, int cols){

    int i, j;               /* Iteration Variables */
    vector <IVec> crop;     /* The vector that is cropped */
    
   /* Resize the vector */
    crop.resize(rows);
    for (i=0; i<rows; i++){
        crop[i].resize(cols);
    }

    for (i=0; i<rows; i++){
        for (j=0; j<cols; j++){
            crop[i][j] = p[i+r][j+c];
        }
    }

    p = crop;
}

// DO NOT CHANGE ANYTHING BELOW THIS LINE

void bad_pgm(string s)
{
  cerr << "Bad PGM file: " << s << endl;
  exit(1);

}

vector <IVec> pgm_read()
{
  string s;
  int r, c, i, j, v;
  vector <IVec> p;

  if (!(cin >> s)) bad_pgm("Empty file.");
  if (s != "P2") bad_pgm("First word is not P2.");
  if (!(cin >> c) || c <= 0) bad_pgm("Bad column spec.");
  if (!(cin >> r) || r <= 0) bad_pgm("Bad column spec.");
  if (!(cin >> i) || i != 255) bad_pgm("Bad spec of 255.");
  p.resize(r);
  for (i = 0; i < r; i++) for (j = 0; j < c; j++) {
    if (!(cin >> v) || v < 0 || v > 255) bad_pgm("Bad pixel.");
    p[i].push_back(v);
  }
  if (cin >> s) bad_pgm("Extra stuff at the end of the file.");
  return p;
}

void usage()
{
  cerr << "usage: pgm_editor command....\n\n";
  cerr << "        CREATE rows cols pixvalue\n";
  cerr << "        CW\n";
  cerr << "        CCW\n";
  cerr << "        PAD pixels pixvalue\n";
  cerr << "        PANEL r c\n";
  cerr << "        CROP r c rows cols\n";
  exit(1);
}

main(int argc, char **argv)
{
  istringstream ss;
  int r, c, i, j, p, w, rows, cols;
  vector <IVec> pgmf;
  string a1;

  if (argc < 2) usage();
  a1 = argv[1];

  if (a1 == "CREATE") {
    if (argc != 5) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c <= 0) usage();
    ss.clear(); ss.str(argv[4]); if (!(ss >> p) || p < 0 || p > 255) usage();
    pgmf = pgm_create(r, c, p);
  } else if (a1 == "PAD") {
    if (argc != 4) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> w) || w <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> p) || p < 0 || p > 255) usage();
    pgmf = pgm_read();
    pgm_pad(pgmf, w, p);
  } else if (a1 == "CCW") {
    if (argc != 2) usage();
    pgmf = pgm_read();
    pgm_ccw(pgmf);
  } else if (a1 == "CW") {
    if (argc != 2) usage();
    pgmf = pgm_read();
    pgm_cw(pgmf);
  } else if (a1 == "PANEL") {
    if (argc != 4) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c <= 0) usage();
    pgmf = pgm_read();
    pgm_panel(pgmf, r, c);
  } else if (a1 == "CROP") {
    if (argc != 6) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r < 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c < 0) usage();
    ss.clear(); ss.str(argv[4]); if (!(ss >> rows) || rows <= 0) usage();
    ss.clear(); ss.str(argv[5]); if (!(ss >> cols) || cols <= 0) usage();
    pgmf = pgm_read();
    if (r + rows > pgmf.size() || c + cols > pgmf[0].size()) {
      fprintf(stderr, "CROP - Bad params for the pictures size (r=%d, c=%d)\n",
           (int) pgmf.size(), (int) pgmf[0].size());
      exit(1);
    }
    pgm_crop(pgmf, r, c, rows, cols);
  } else {
    usage();
  }
  pgm_write(pgmf);
}
