/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * hello1.cpp
 *
 * GNU ARM Compiler and Debugger Workbook example to demonstrate
 * arm-elf-gcc. 
 *
 * ================================================================== */
#include <iostream>
using namespace std;

extern void subroutine(void);

int main() {
  cout << "Hello World from main\n";
  subroutine();
  cout << "Goodbye from main\n";
  return 0;
}

