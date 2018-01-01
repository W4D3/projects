#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

main(int argc, char **argv)
{
  string s, s2;
  unsigned char c;
  int i;

  printf("s\n");
  for (i = 0; i < 11; i++) {
    getline(cin, s);
    getline(cin, s2);
    s.push_back('\n');
    s += s2;
    c = s.length();
    fwrite(&c, 1, 1, stdout);
    cout << s << endl;
  }
}
