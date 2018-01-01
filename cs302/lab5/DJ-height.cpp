#include <vector>
#include <cstdlib>
#include <iostream>
#include "DJ.h"
using namespace std;

Disjoint::Disjoint(int nelements)
{
  links.resize(nelements, -1);
  ranks.resize(nelements, 1);
}

int Disjoint::Union(int s1, int s2)
{
  int p, c;

  if (links[s1] != -1 || links[s2] != -1) {
    cerr << "Must call union on a set, and not just an element.\n";
    exit(1);
  }
  if (ranks[s1] > ranks[s2]) {
    p = s1;
    c = s2;
  } else {
    p = s2;
    c = s1;
  }
  links[c] = p;
  if (ranks[s1] == ranks[s2]) ranks[p]++; 
  return p;
}

int Disjoint::Find(int element)
{
  while (links[element] != -1) element = links[element];
  return element;
}

void Disjoint::Print()
{
  int i;
  printf("\n");
  printf("Elts: "); for (i = 0; i < links.size(); i++) printf(" %2d", i); printf("\n");
  printf("Links:"); for (i = 0; i < links.size(); i++) printf(" %2d", links[i]); printf("\n");
  printf("Ranks:"); for (i = 0; i < links.size(); i++) printf(" %2d", ranks[i]); printf("\n");
  printf("\n");
}
