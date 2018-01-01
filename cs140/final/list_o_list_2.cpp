#include <iostream>
#include <list>
using namespace std;

typedef list <int> intlist;

main()
{
  list <intlist> numlists;
  list <intlist>::iterator nlit;
  intlist il;
  intlist::iterator ilit;
  int i, j;

  for (j = 0; j < 100; j += 10) {
    numlists.push_back(il);
    for (i = 0; i < 10; i++) {
      il.push_back(i+j);
    }
  }

  for (nlit = numlists.begin(); nlit != numlists.end(); nlit++) {
    il = *nlit;
    for (ilit = il.begin(); ilit != il.end(); ilit++) cout << *ilit << " " ;
    cout << endl;
  }
}
