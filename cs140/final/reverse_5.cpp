#include <iostream>
#include <deque>
using namespace std;

main()
{
  deque <string> lines;
  int i;
  string s;

  while (getline(cin, s)) lines.push_front(s);

  for (i = 0; i < lines.size(); i++) cout << lines[i] << endl;
}
