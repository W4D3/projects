#include <iostream>
#include <vector>
using namespace std;

main()
{
  vector <string> lines;
  vector <string>::iterator lit;
  string s;

  while (getline(cin, s)) lines.insert(lines.begin(), s);
 
  for (lit = lines.begin(); lit != lines.end(); lit++) {
    cout << *lit << endl;
  }
}
