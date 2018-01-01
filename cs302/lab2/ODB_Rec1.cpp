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
#define O1(v) cout << v << endl
#define O2(v1, v2) cout << v1 << " " << v2 << endl
#define O3(v1, v2, v3) cout << v1 << " " << v2 << " " << v3 << endl
#define OVEC(v) { int iii; VIT(iii, v) cout << v[iii] << " " ; cout << endl; }
typedef vector <int> IVec;

class OneDimensionalBalls {
  public:
    long long countValidGuesses(vector <int> firstPicture, vector <int> secondPicture);
    long long cvg(int v, int index);
    vector <int> FP;
    vector <int> SP;
    vector <int> Matched;
    map <int, int> SP_Balls;
};

long long OneDimensionalBalls::cvg(int v, int index)
{
  long long rv;
  int second_val, sb_index;
  map <int, int>::iterator mit;
  int i;

  rv = 0;

  for (i = -1; i <= 1; i += 2) {
    second_val = FP[index]+v*i;
    mit = SP_Balls.find(second_val);
    if (mit != SP_Balls.end() && !(Matched[mit->second])) {
      if (index+1 == FP.size()) {
        rv++;
      } else {
        Matched[mit->second] = 1;
        rv += cvg(v, index+1);
        Matched[mit->second] = 0;
      }
    }
  }
  return rv;
}

long long OneDimensionalBalls::countValidGuesses(
      vector <int> firstPicture, 
      vector <int> secondPicture)
{
  int i;

  FP = firstPicture;
  SP = secondPicture;
  Matched.resize(SP.size(), 0);
  VIT(i, secondPicture) SP_Balls[SP[i]] = i;

  return cvg(1, 0);
}
