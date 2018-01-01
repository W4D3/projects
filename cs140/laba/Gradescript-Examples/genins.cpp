#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)
#define FUP(i, n) for (i = 0; i < n; i++)

typedef map<int, string> ISmap;
typedef map<int, int> IImap;
typedef map<string, int> SImap;
typedef map<string, string> SSmap;

typedef ISmap::iterator ISmit;
typedef IImap::iterator IImit;
typedef SSmap::iterator SSmit;
typedef SImap::iterator SImit;

typedef vector <int> IVec;
typedef vector <double> DVec;
typedef vector <string> SVec;

main(int argc, char **argv)
{
  int ne, e, la, lh, lo, lp, lr, ls, r, r2;
  SVec m;
  string s;

  srand48(time(0));
  if (argc != 2) {
    fprintf(stderr, "usage: genins nevents\n");
    exit(1);
  }

  ne = atoi(argv[1]);

  la = -2;
  lh = -2;
  lo = -2;
  lp = -2;
  lr = -2;
  ls = -2;

  for (e = 0; e < ne; e++) {

    r = lrand48()%100;

    if (r < 20 || r > 75) {
      if (!getline(cin, s)) {
        fprintf(stderr, "Standard in empty\n");
        exit(1);
      }
      printf("INSERT %s %03ld-%03ld-%04ld %03ld-%02ld-%04ld\n", s.c_str(),
        lrand48()%1000, lrand48()%1000, lrand48()%10000,
        lrand48()%1000, lrand48()%100, lrand48()%10000);
      m.push_back(s);
    } else if (r < 23) {
      if (lp == e-1) {
        e--;
      } else {
        lp = e;
        printf("PRINT\n");
      }
    } else if (r < 27) {
      if (lr == e-1) {
        e--;
      } else {
        lr = e;
        printf("PREORDER\n");
      }
    } else if (r < 30) {
      if (lo == e-1) {
        e--;
      } else {
        lo = e;
        printf("POSTORDER\n");
      }
    } else if (r < 40) {
      if (m.size() == 0) {
        e--;
      } else {
        r2 = lrand48()%m.size();
        printf("DELETE %s\n", m[r2].c_str());
        m[r2] = m[m.size()-1];
        m.pop_back();
      }
    } else if (r < 42) {
        if (!getline(cin, s)) {
          fprintf(stderr, "Standard in empty\n");
          exit(1);
        }
        printf("DELETE %s\n", s.c_str());
    } else if (r < 45) {
        r2 = lrand48()%m.size();
        printf("INSERT %s %03ld-%03ld-%04ld %03ld-%02ld-%04ld\n", m[r2].c_str(),
          lrand48()%1000, lrand48()%1000, lrand48()%10000,
          lrand48()%1000, lrand48()%100, lrand48()%10000);
    } else if (r < 48) {
      if (ls == e-1) {
        e--;
      } else {
        ls = e;
        printf("SORT\n");
      }
    } else if (r < 53) {
      if (m.size() == 0) {
        e--;
      } else {
        printf("FIND %s\n", m[lrand48()%m.size()].c_str());
      }
    } else if (r < 55) {
        if (!getline(cin, s)) {
          fprintf(stderr, "Standard in empty\n");
          exit(1);
        }
        printf("FIND %s\n", s.c_str());
    } else if (r < 58) {
        if (!getline(cin, s)) {
          fprintf(stderr, "Standard in empty\n");
          exit(1);
        }
        printf("ROTATE %s\n", s.c_str());
    } else if (r < 65) {
      if (m.size() == 0) {
        e--;
      } else {
        printf("ROTATE %s\n", m[lrand48()%m.size()].c_str());
      }
    } else if (r < 68) {
        if (!getline(cin, s)) {
          fprintf(stderr, "Standard in empty\n");
          exit(1);
        }
        printf("DEPTH %s\n", s.c_str());
    } else if (r < 72) {
      if (m.size() == 0) {
        e--;
      } else {
        printf("DEPTH %s\n", m[lrand48()%m.size()].c_str());
      }
    } else if (r < 75) {
      if (la == e-1) {
        e--;
      } else {
        la = e;
        printf("ISAVL\n");
      }
    } else if (r < 78) {
      if (lh == e-1) {
        e--;
      } else {
        lh = e;
        printf("HEIGHT\n");
      }
    } else {
      e--;
    }
  }
  if (lp != e-1) printf("PRINT\n");
  exit(0);
}

