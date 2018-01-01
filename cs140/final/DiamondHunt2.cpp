#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <list>
using namespace std;

class DiamondHunt {
  public:
    int countDiamonds(string mine);
};

int DiamondHunt::countDiamonds(string mine)
{
  int nd, i;
  list <char> l;
  list <char>::iterator left, right, newleft;

  for (i = 0; i < mine.size(); i++) l.push_back(mine[i]);
  
  nd = 0;
  left = l.begin();
  while (left != l.end()) {
    if (*left == '>') {
      left++;             // If left is not the beginning of a diamond, move on.
    } else {
      right = left;
      right++;
      if (right == l.end()) return nd;

      if (*right == '<') {   // If right is not the end of a diamond, move on
        left++;
      } else {            // Otherwise, we've found a diamond.  We need to
        nd++;             // increment nd, and set newleft to point to the previous
                          // char, or if left is at the beginning, to the next one.

        if (left == l.begin()) {
          newleft = right;
          newleft++;
        } else {
          newleft = left;
          newleft--;
        }

        l.erase(left);      // Now erase left and right, and set left to newleft.
        l.erase(right);
        left = newleft;
      }
    }

    cout << "left: " << *left <<endl;
    cout << "right: " << *right <<endl;
  }
  return nd;
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

