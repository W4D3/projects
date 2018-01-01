#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)
#define FUP(i, n) for (i = 0; i < n; i++)

typedef vector <string> SVec;
typedef vector <int> IVec;

string gen_random_key()
{
  string digs = "0123456789abcdef";
  int ks, i;
  string rv;

  ks = lrand48()%60 + 10;
  for (i = 0; i < ks; i++) {
    rv.push_back(digs[lrand48()%digs.size()]);
  }
  return rv;
}


main(int argc, char **argv)
{
  int nfind, nadd;
  int i, e;
  string s, k;
  SVec keys;
  IVec events;
  int nevents;
  ifstream f;
  istringstream ss;

  srand48(time(0));
  nfind = 0;
  if (argc == 1 || argc > 7) {
    cerr << "usage: genrandom nadd nfind nmiss nprint nprobe dict\n";
    exit(1);
  } 

  if (argc == 7) {
    f.open(argv[6]);
    if (f.fail()) { perror(argv[6]); exit(1); }
    while (getline(f, s)) {
      ss.clear();
      ss.str(s);
      ss >> s;
      keys.push_back(s);
    }
  }
  events.resize(5, 0);
  for (i = 1; i < argc && i < 6; i++) events[i-1] = atoi(argv[i]);
  nevents = 0;
  VIT(i, events) nevents += events[i];

  while (nevents > 0) {
    e = lrand48()%nevents;
    for (i = 0; e >= 0; i++) e -= events[i];
    for (i--; events[i] == 0; i--) ;
    if (i == 0) {
      cin >> s;
      k = gen_random_key();
      keys.push_back(k);
      printf("ADD %s %s\n", k.c_str(), s.c_str());
      events[0]--;
      nevents--;
    } else if (i == 1) {
      if (keys.size() > 0) {
        printf("FIND %s\n", keys[lrand48()%keys.size()].c_str());
        events[i]--;
        nevents--;
      }
    } else if (i == 2) {
      if (keys.size() > 0) {
        printf("FIND %s\n", gen_random_key().c_str());
        events[i]--;
        nevents--;
      }
    } else if (i == 3) {
      if (events[i] > 1 || nevents == 1) {
        printf("PRINT\n");
        events[i]--;
        nevents--;
      }
    } else if (i == 4) {
      if (events[i] > 1 || nevents == events[i-1]+1) {
        printf("TPROBES\n");
        events[i]--;
        nevents--;
      }
    }
  }
}

