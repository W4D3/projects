#include <string>
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

typedef vector <string> SVec;
typedef vector <int> IVec;

main()
{
  int i, j;
  string s1, s2;
  IVec ok;

  ok.resize(1000, 0);
  while (i < 5) {
    cin >> j >> s1 >> s2;
    if (ok[j] == 0) {
      cout << "ADD " << s1 << " " << s2 << endl;
      ok[j] = 1;
      i++;
    }
  }
  printf("PRINT\n");
}
    
