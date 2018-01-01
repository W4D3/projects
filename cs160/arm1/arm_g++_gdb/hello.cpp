/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * hello.cpp
 *
 * GNU ARM Compiler and Debugger Workbook example to demonstrate
 * arm-elf-gcc.
 *
 * ================================================================== */
#include <iostream>
using namespace std;

void subroutine (void); // Declare signature before use 

int main() {
  cout << "Hello World from main\n";
  subroutine();
  cout << "Goodbye from main\n";
  return 0;
}

void subroutine() {
  cout << "Hello from subroutine\n";
}
