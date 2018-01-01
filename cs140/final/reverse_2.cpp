#include <iostream>
#include <list>
using namespace std;

main()
{
  list <string> lines;
  list <string>::reverse_iterator lit;
  string s;

  while (getline(cin, s)) lines.push_back(s);
 
  for (lit = lines.rbegin(); lit != lines.rend(); lit++) {
    cout << *lit << endl;
  }
}
