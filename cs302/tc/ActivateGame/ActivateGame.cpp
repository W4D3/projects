#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "DJ.h"
#include <cmath>

using namespace std;

class Edge {
    public:
        int to;
        int from;
        int weight;
};

class ActivateGame {
    public:
        int findMaxScore(vector <string> grid);
        Edge *e;
};

int ActivateGame::findMaxScore(vector <string> grid)
{
    int i, j, s1, s2, rv, a, b;
    //int c = grid[0].size();
    vector <int> table(256, 0);
    multimap <int, Edge *> m;
    multimap <int, Edge *>::reverse_iterator mit;
    Disjoint d(grid.size()*grid[0].size());

    // Create the table for the edge weights
    for (i = '0'; i <= '9'; i++) {
        table[i] = i - '0';
    }

    for (i = 'A'; i <= 'Z'; i++) {
        table[i] = i - 'A' + 36;
    }

    for (i = 'a'; i <= 'z'; i++) {
        table[i] = i - 'a' +10;
    }

    // Create the edges
    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[i].size(); j++) {

            // Create a right edge
            if (j < grid[i].size()-1) {
                e = new Edge;
                e->from = i*grid[0].size()+j;
                e->to = i*grid[0].size()+(j+1);
                a = table[grid[i][j]];
                b = table[grid[i][j+1]];
                e->weight = abs(a-b);
                m.insert(make_pair(e->weight, e));
            }

            // Create a down edge
            if (i < grid.size()-1) {
                e = new Edge;
                e->from = i*grid[0].size()+j;
                e->to = (i+1)*grid[0].size()+j;
                a = table[grid[i][j]];
                b = table[grid[i+1][j]];
                e->weight = abs(a-b);
                m.insert(make_pair(e->weight, e)); 
            }
        }
    }

    // Kruskals Algorithm
    rv = 0;
    for (mit = m.rbegin(); mit != m.rend(); mit++) {
        
        s1 = d.Find(mit->second->from); 
        s2 = d.Find(mit->second->to);
        
        if (s1 != s2) {
            d.Union(s1, s2);
            rv += mit->first;
        }
    }

    return rv;
}
