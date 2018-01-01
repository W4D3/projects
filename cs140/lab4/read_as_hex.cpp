#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

main()
{
  string s;
  istringstream ss;
  int i;

  while (cin >> s) {
    ss.clear();
    ss.str(s);
    if (ss >> hex >> i) printf("%d 0x%x\n", i, i);
  }
}
