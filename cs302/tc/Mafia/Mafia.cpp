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

class Mafia {
      public:
              int play(vector &lt;int&gt; guilt, vector &lt;string&gt; responses, int playerIndex);
              int Rplay(vector &lt;int&gt; guilt, vector &lt;string&gt; responses, int playerIndex);
};

int Mafia::play(vector &lt;int&gt; guilt, vector &lt;string&gt; responses, int playerIndex)
{
      int i;
}

int Rplay(vector &lt;int&gt; guilt, vector &lt;string&gt; responses, int playerIndex)
{

}
