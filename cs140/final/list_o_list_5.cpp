#include <iostream>
#include <list>
using namespace std; typedef list <int> intlist; main() { list <intlist> numlists; list <intlist>::iterator nlit; intlist il; intlist::iterator ilit; int i, j; for (j = 0; j < 100; j += 10) { numlists.resize(numlists.size()+1); for (i = 0; i < 10; i++) { numlists.back().push_back(i+j); } } for (nlit = numlists.begin(); nlit != numlists.end(); nlit++) { for (ilit = nlit->begin(); ilit != nlit->end(); ilit++) cout << *ilit << " " ; cout << endl; } }
