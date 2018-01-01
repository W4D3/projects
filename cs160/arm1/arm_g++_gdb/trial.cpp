/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * trial.cpp
 *
 * GNU ARM Compiler and Debugger Workbook example to demonstrate
 * arm-elf-gdb.
 *
 * ================================================================== */

#include <iostream>
using namespace std;

#define BLOCKSTART (int *) 0x4000
#define BLOCKEND   (int *) 0x4100
#define TESTADDR   (int *) 0x4200

/* Memory initialization to zero */
static void initmem() {
  int *i;
  int a;

  a = 0;
  i=BLOCKSTART;

  do {
    *i++ = 0;
    a++;
  } while (i<BLOCKEND);
}

static void results() {
  cout << "The memory area has now been cleared.\n";
}

static void quickfunc (int a, int b, int c) {
  int x,y,z;
  x = 3;
  y = 4;
  z = x * y;
  x = (z << 8) + y;
}

int main() {
  int *datablock;
  int a,b,c;

  datablock = BLOCKSTART;
  a = 10;
  b = 20;
  c = 30;

  initmem();
  quickfunc(a,b,c);
  quickfunc(b,c,a);
  quickfunc(c,a,b);
  results();
}
