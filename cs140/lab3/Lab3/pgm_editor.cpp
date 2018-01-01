#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

typedef vector <int> IVec;

// Write your code here:

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
