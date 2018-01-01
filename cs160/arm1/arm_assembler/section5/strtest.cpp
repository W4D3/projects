/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM 
 *
 * strtest.cpp
 *
 * Example of calling externally defined ARM subroutines.
 * [GNU ARM Assembler Workbook, Section 5]
 *
 * ================================================================== */

#include <iostream>
using namespace std;

extern "C" { void strcopy (char *d, char *s); }

int main() {
  char *srcstr = "First string - source ";
  char *dststr = "Second string - destination ";

  cout << "Before copying:\n";
  cout << srcstr << endl << dststr << endl;
  strcopy(dststr,srcstr);
  cout << "After copying:\n";
  cout << srcstr << endl << dststr << endl;

  return (0);
}
