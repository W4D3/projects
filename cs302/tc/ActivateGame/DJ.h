#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

class Disjoint {
    public:
        Disjoint(int nelements);
        int Union(int s1, int s2);
        int Find(int element);
        void Print();
    protected:
        vector <int> links;
        vector <int> ranks;
};

