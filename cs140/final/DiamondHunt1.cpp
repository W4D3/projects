#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class DiamondHunt {
  public:
    int countDiamonds(string mine);
};

int DiamondHunt::countDiamonds(string mine)
{
  int nd, i;

  nd = 0;
  while (1) {
    i = mine.find("<>");
    if (i == string::npos) return nd;
    nd++;
    mine = mine.substr(0, i) + mine.substr(i+2);
  }
}

main()
{
  DiamondHunt d;
  string s;

  while (cin >> s) {
    cout << d.countDiamonds(s) << endl;
  }
  exit(0);
}

