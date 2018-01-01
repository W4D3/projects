#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include "city_map.h"

using namespace std;

/* city_map.cpp
   Mitchell Wade
   Nov. 9, 2014

   This program simulates driving through
   a city and gives you back the path that
   the vehicle travels with respect to a
   time variable. It will show you the best,
   worst, and average time that it will take
   to travel through the specified city grid.
 */

// Calculates the distance between two nodes
double Distance(double x1, double x2, double y1, double y2) {

    double distance = 0;

    distance = sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));

    return distance;
}

City_Map::City_Map() {

    int s, a, max_street = -1, max_avenue = -1, i, j;
    double x, y, gS, gA;
    Intersection *I, *in;
    list <Intersection *>::iterator lit;
    vector <vector <Intersection *> > tmp;
    Road_Segment *R;

    // Creates each intersection
    while (cin >> s >> a >> x >> y >> gS >> gA) {
        I = new Intersection;
        I->street = s;
        I->avenue = a;
        I->x = x;
        I->y = y;
        I->green[0] = gS;
        I->green[1] = gA;
        I->backedge = NULL;
        I->best_time = -1;
        I->bfsq_ptr = bfsq.end();
        all.push_back(I);
        
        // Keeps track of the maximum street and avenue number
        if (max_street == -1 || max_street < s) max_street = s;
        if (max_avenue == -1 || max_avenue < a) max_avenue = a;
    }

    // Create enough space for each intersection node
    tmp.resize(max_street+1);
    for (i = 0; i < max_street+1; i++) {
        tmp[i].resize(max_avenue+1);
    }

    // Create the graph
    for (lit = all.begin(); lit != all.end(); lit++) {   

        // Grab the intersection node
        in = *lit;

        // Set it in the vector to the proper position in the graph
        tmp[in->street][in->avenue] = in;
    }

    // Create the edges
    for (lit = all.begin(); lit != all.end(); lit++) {

        // Grab the intersection node and set pointers
        in = *lit;
        i = in->street;
        j = in->avenue;

        // Set the first and last intersection
        if (i == 0 && j == 0) first = in;
        if (i == max_street && j == max_avenue) last = in;

        // Check North
        if ((i != max_street) && ((j%2 == 0) || (j%5 == 0) || (j == max_avenue))) {
            
            R = new Road_Segment();
            R->type = AVENUE;
            R->number = j;
            R->distance = Distance(in->x, (tmp[i+1][j])->x, in->y, (tmp[i+1][j])->y);
            R->from = tmp[i][j];
            R->to = tmp[i+1][j];
            R->from->adj.push_back(R);
        }

        // Check West
        if ((j != max_avenue) && ((i%2 == 0) || (i%5 == 0))) {

            R = new Road_Segment();
            R->type = STREET;
            R->number = i;
            R->distance = Distance(in->x, (tmp[i][j+1])->x, in->y, (tmp[i][j+1])->y);
            R->from = tmp[i][j];
            R->to = tmp[i][j+1];
            R->from->adj.push_back(R);
        }

        // Check South
        if ((i != 0) && ((j%2 == 1) || (j%5 == 0) || (j == max_avenue))) {

            R = new Road_Segment();
            R->type = AVENUE;
            R->number = j;
            R->distance = Distance(in->x, (tmp[i-1][j])->x, in->y, (tmp[i-1][j])->y);
            R->from = tmp[i][j];
            R->to = tmp[i-1][j];
            R->from->adj.push_back(R);
        }

        // Check East
        if ((j != 0) && ((i%2 == 1) || (i%5 == 0))) {

            R = new Road_Segment();
            R->type = STREET;
            R->number = i;
            R->distance = Distance(in->x, (tmp[i][j-1])->x, in->y, (tmp[i][j-1])->y);
            R->from = tmp[i][j];
            R->to = tmp[i][j-1];
            R->from->adj.push_back(R);
        }
    }
}

double City_Map::Dijkstra(int avg_best_worst) {

    int i;
    double R, G;
    double currentT = 0, timeTraveled = 0;
    Intersection *currentI, *intersectionTo;
    list <class Road_Segment *>::iterator lit;
    Road_Segment *rs;

    // Put the first node on the queue and set the
    // bfsq_ptr for the first intersection
    first->best_time = 0;
    first->bfsq_ptr = bfsq.insert(make_pair(0, first));

    // Find the shortest path
    while (!bfsq.empty()) {

        // Save the current time and intersection
        currentT = bfsq.begin()->first;
        currentI = bfsq.begin()->second;

        // Remove the most recent node from the queue
        bfsq.erase(bfsq.begin());

        // Update the path if at the last intersection
        if (currentI == last) {

            while (currentI->backedge->from != first) {
                path.push_front(currentI->backedge);
                currentI = currentI->backedge->from;
            }
            path.push_front(currentI->backedge);

            return -1;
        }

        // Go through all edges in the adj list of the intersection node
        for (lit = currentI->adj.begin(); lit != currentI->adj.end(); lit++) {

            // Keeps track of current intersection and total time
            rs = *lit;
            intersectionTo = rs->to;
            timeTraveled = (rs->distance/(30.0/3600.0));

            // Set the time for a red and green light
            R = intersectionTo->green[!rs->type];
            G = intersectionTo->green[rs->type];

            // Account for the worst case and the avg. case if selected
            if (avg_best_worst == 'W') timeTraveled += R;
            if (avg_best_worst == 'A') timeTraveled += (( R*R)/(2*(R+G)));

            // Update the time
            timeTraveled += currentI->best_time;

            // Update the queue
            if (intersectionTo->best_time == -1 || intersectionTo->best_time > timeTraveled) {
                
                if(intersectionTo->best_time != -1) bfsq.erase(intersectionTo->bfsq_ptr);

                intersectionTo->best_time = timeTraveled;
                intersectionTo->backedge = rs;
                intersectionTo->bfsq_ptr = bfsq.insert(make_pair(intersectionTo->best_time, intersectionTo));
            }
        }
    }

    // Return the shortest path
    return last->best_time;
    //return 0;
}
