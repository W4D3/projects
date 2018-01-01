#include "./BuildingAdvertise.cpp"
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
  int i;
  class BuildingAdvertise TheClass;
  long long retval;
  vector <int> h;
  int n;
  string s;
  stringstream ss;

  if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

 if (atoi(argv[1]) == -1) {
   if (!getline(cin, s)) {
     fprintf(stderr, "You need two lines: One of integers for h, and a single integer for n\n");
     exit(1);
   }
   ss.clear(); ss.str(s);
   while (ss >> i) h.push_back(i);
   if (!(cin >> n) || n <= 0) {
     fprintf(stderr, "You need two lines: One of integers for h, and a single integer for n\n");
     exit(1);
   }
 }


 if (atoi(argv[1]) == 0) {
    h.push_back(3);
    h.push_back(6);
    h.push_back(5);
    h.push_back(6);
    h.push_back(2);
    h.push_back(4);
    n = 6;
  }

 if (atoi(argv[1]) == 1) {
    h.push_back(5);
    h.push_back(0);
    h.push_back(7);
    h.push_back(0);
    h.push_back(2);
    h.push_back(6);
    h.push_back(2);
    n = 7;
  }

 if (atoi(argv[1]) == 2) {
    h.push_back(1048589);
    h.push_back(2097165);
    n = 100000;
  }

 if (atoi(argv[1]) == 3) {
    h.push_back(1);
    h.push_back(7);
    h.push_back(2);
    h.push_back(5);
    h.push_back(3);
    h.push_back(1);
    n = 6;
  }

  retval = TheClass.getMaxArea(h, n);
  cout << retval << endl;

  exit(0);
}
