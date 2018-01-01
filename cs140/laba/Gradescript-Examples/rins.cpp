#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

main()
{
  string s;
  srand48(time(0));

  while (getline(cin, s)) {
    printf("INSERT %s %03ld-%03ld-%04ld %03ld-%02ld-%04ld\n",
    s.c_str(),
    lrand48()%1000,
    lrand48()%1000,
    lrand48()%10000,
    lrand48()%1000,
    lrand48()%100,
    lrand48()%10000);
  }
  exit(0);
}
