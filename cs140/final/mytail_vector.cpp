#include <iostream>
#include <vector>
using namespace std;

main()
{
  vector <string> lines;
  vector <string>::iterator lit;
  string s;

  while (getline(cin, s)) {
    lines.push_back(s);
    if (lines.size() > 10) lines.erase(lines.begin());
  }
 
  for (lit = lines.begin(); lit != lines.end(); lit++) {
    cout << *lit << endl;
  }
}
