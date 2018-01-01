#include <string>
#include <sstream>
#include "incremental_inverse.h"

void StoSVec(string &s, vector <string> &sv)
{
  istringstream ss;
  string s2;

  ss.clear();
  ss.str(s);
  sv.clear();
  while (ss >> s2) sv.push_back(s2);
}

void usage(string s)
{
  fprintf(stderr, "usage: ii_test rows w\n");
  fprintf(stderr, "       w = 8, 16 or 32\n");
  if (s != "") cerr << endl << s << endl;
  exit(0);
}

main(int argc, char **argv)
{
  int w, c, i;
  string s;
  vector <string> sv;
  vector <unsigned int> v;
  Incremental_Inverse *II;
  Galois_Field *GF;

  if (argc != 3) usage("");
  if (sscanf(argv[2], "%d", &w) != 1 || (w != 8 && w != 16 && w != 32)) usage("Bad w.");
  if (sscanf(argv[1], "%d", &c) != 1 || c <= 0) usage("Bad rows");

  GF = new Galois_Field(w);
  II = new Incremental_Inverse(c, GF);

  while(1) {
    cout << "II_TEST> ";
    cout.flush();
    if (!getline(cin, s)) exit(0);
    StoSVec(s, sv);
    if (sv.size() == 0) {
    } else if (sv[0] == "ADD") {
      if (sv.size() != c + 1) {
        printf("Your cols need to be of size: %d\n", c);
      } else {
        v.clear();
        for (i = 1; i < sv.size(); i++) {
          v.push_back(atoi(sv[i].c_str()));
        }
        if (II->Add_Col(v)) {
          printf("Successful\n");
        } else {
          printf("Unsuccessful\n");
        }
      }
    } else if (sv[0] == "DELETE") {
      if (sv.size() != 1) {
        printf("DELETE has no extra arguments\n", c);
      } else {
        II->Delete_Col();
      }
    } else if (sv[0] == "QUIT") {
      exit(0);
    } else if (sv[0] == "PRINT") {
      if (sv.size() != 1) {
        printf("PRINT has no extra arguments\n", c);
      } else {
        II->Print();
      }
    } else {
      printf("Unknown command %s\n", sv[0].c_str());
      printf("Commands are: ADD DELETE PRINT and QUIT\n", sv[0].c_str());
    }
  }
} 
