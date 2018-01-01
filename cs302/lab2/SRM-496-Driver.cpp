#include "./OneDimensionalBalls.cpp"
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
  int i;
  class OneDimensionalBalls TheClass;
  long long retval;
  vector <int> firstPicture;
  vector <int> secondPicture;
  string s;
  stringstream ss;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (-1 reads from stdin)\n"); exit(1); }

 if (atoi(argv[1]) == -1) {
   if (!getline(cin, s)) {
     fprintf(stderr, "You need two lines of integers\n");
     exit(1);
   }
   ss.clear(); ss.str(s);
   while (ss >> i) firstPicture.push_back(i);
   if (!getline(cin, s)) {
     fprintf(stderr, "You need two lines of integers\n");
     exit(1);
   }
   ss.clear(); ss.str(s);
   while (ss >> i) secondPicture.push_back(i);
 }

 if (atoi(argv[1]) == 0) {
    firstPicture.push_back(12);
    firstPicture.push_back(11);
    secondPicture.push_back(10);
    secondPicture.push_back(11);
    secondPicture.push_back(13);
  }

 if (atoi(argv[1]) == 1) {
    firstPicture.push_back(1);
    firstPicture.push_back(2);
    firstPicture.push_back(3);
    secondPicture.push_back(1);
    secondPicture.push_back(2);
    secondPicture.push_back(3);
  }

 if (atoi(argv[1]) == 2) {
    firstPicture.push_back(1);
    firstPicture.push_back(3);
    secondPicture.push_back(1);
    secondPicture.push_back(3);
  }

 if (atoi(argv[1]) == 3) {
    firstPicture.push_back(7234);
    secondPicture.push_back(6316);
    secondPicture.push_back(689156);
    secondPicture.push_back(689160);
    secondPicture.push_back(689161);
    secondPicture.push_back(800000);
    secondPicture.push_back(1000001);
  }

 if (atoi(argv[1]) == 4) {
    firstPicture.push_back(6);
    firstPicture.push_back(2);
    firstPicture.push_back(4);
    secondPicture.push_back(1);
    secondPicture.push_back(2);
    secondPicture.push_back(3);
    secondPicture.push_back(4);
    secondPicture.push_back(5);
    secondPicture.push_back(7);
    secondPicture.push_back(8);
  }

 if (atoi(argv[1]) == 5) {
    for (i = 1; i <= 50; i++) {
      secondPicture.push_back(i);
      if (i%2 == 0 && i < 50) firstPicture.push_back(i);
    }
  }

 if (atoi(argv[1]) == 6) {
    for (i = 9; i <= 40; i++) firstPicture.push_back(i);
    for (i = 0; i <= 49; i++) secondPicture.push_back(i);
  }

  retval = TheClass.countValidGuesses(firstPicture, secondPicture);
  cout << retval << endl;

  exit(0);
}
