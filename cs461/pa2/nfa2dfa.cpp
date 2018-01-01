// nfa2dfa.c++
// Mitchell Wade
// CS461 - Compilers

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

typedef vector <int> IVec;
typedef vector <string> SVec;
typedef vector <double> DVec;

class NFA {
   public:
      vector <string> chars;

};


void output(int initialState, vector <int> finalStates, int totalStates, 
            vector <string> dfaSymbols) {

   int i = 0;

   printf("Final DFA:\n");
   printf("Initial State: %d\n", initialState);
   for (i = 0; i < finalStates.size(); i++) {
      if (finalStates.size() == 1) {
         printf("Final State: {");
         printf("%d", finalStates[i]);
         printf("}\n");
      }
      if (finalStates.size() >= 1) {
         if (i == 0) printf("Final States: {");
         printf("%d", finalStates[i]);
         if (i != finalStates.size()-1) printf(",");
         if (i == finalStates.size()-1) printf("}\n");
      }
   }
   printf("Total States: %d\n", totalStates);
   for (i = 0; i < dfaSymbols.size(); i++) {
      if (i == 0) printf("State: ");
      printf("%10s", dfaSymbols[i].c_str());
      if (i == dfaSymbols.size()-1) printf("\n");
   }
}

int main(int argc, char** argv) {

   int l = 0, w = 0, currentState = 0;
   int i = 0, j = 0, k = 0, initialState, totalStates;
   string s, state, symbol;
   istringstream ss;
   vector <int> finalStates;
   vector <string> nfaSymbols;
   vector <string> dfaSymbols;
   vector <int> tmpStates;
   vector <int> curStates;
   vector <string> tmpSymbols;
   map <string, int> transitions;
   map <string, int>::iterator tit;

   cout << "reading NFA ..." << endl;
   cout << endl;

   while (getline(cin, s)) {
      l++;
      ss.clear();
      ss.str(s);
      w = 0;
      while (ss >> s) {
         w++;
         //printf("Line %3d, word %3d: %s\n", l, w, s.c_str());

         // Create initial state
         if (s  == "Initial") {
            ss >> s;
            ss.clear();
            ss >> s;
            initialState = atoi(s.c_str());
         }

         // Create final states vector
         if (s == "Final") {
            ss >> s;
            ss.clear();
            ss >> s;
            for (i = 0; i < s.size(); i++) {
               if (s[i] == ',') {
                  finalStates.push_back(atoi(state.c_str()));
                  state = "";
                  
               }
               if (isdigit(s[i])) {
                  state += s[i];
               }
            }
            if (state != "") finalStates.push_back(atoi(state.c_str()));
         }

         // Create total states
         if (s == "Total") {
            ss >> s;
            ss.clear();
            ss >> s;
            totalStates = atoi(s.c_str());
         }

         // Create states
         if (s == "State") {
            while(ss >> s) {
               nfaSymbols.push_back(s.c_str());
               s.clear();
            }
         }

         // Create transitions
         currentState = atoi(s.c_str()); 
         printf("currentState = %d\n", currentState);
         i = 0;
         state = "";
         while(ss >> s) {
            printf("s: %s\n", s.c_str());
            if (s != "{}") {
               symbol = nfaSymbols[i];
               printf("symbol: %s\n", symbol.c_str());
               for (j = 0; j < s.size(); j++) {
                  if (s[j] != '{' && s[j] != ',' && s[j] != '}') {
                     state += s[j];
                     printf("state: %s\n", state.c_str());
                  }
                  if (s[j] == ',') {
                     transitions.insert(make_pair(symbol, atoi(state.c_str())));
                     tmpStates.push_back(atoi(state.c_str()));
                     tmpSymbols.push_back(symbol);
                     curStates.push_back(currentState);
                     printf("transition: %s\n", state.c_str());
                     state = "";
                  }
               }
               if (state != "") {
                  transitions.insert(make_pair(symbol, atoi(state.c_str())));
                  tmpStates.push_back(atoi(state.c_str()));
                  tmpSymbols.push_back(symbol);
                  curStates.push_back(currentState);
                  printf("transition: %s\n", state.c_str());
                  state = "";
               }
            }
               /*for (j = 0; j < s.size(); j++) {
                     if (s[j] == ',') {
                        tmpStates.push_back(atoi(state.c_str()));
                        transitions.insert(make_pair(symbol, atoi(state.c_str())));
                        state = "";
                     }
                     //if (isdigit(s[j])) {
                        state += s[j];
                     //}
               }*/
               /*if (state != "") {
                  tmpStates.push_back(atoi(state.c_str()));
                  transitions.insert(make_pair(symbol, atoi(state.c_str())));
                  state = "";
               }*/
            
            // Go to next symbol}
            i++;
         }

         /*for (i = 0; i < tmpStates.size(); i++) {
            transitions.insert(make_pair(symbol, atoi(state.c_str())));
         }*/
      }
   }
   
   // Create dfaSymbols vector
   for (i = 0; i < nfaSymbols.size(); i++) {
      if (nfaSymbols[i] != "E") dfaSymbols.push_back(nfaSymbols[i]);
   }

   cout << "creating corresponding DFA ..." << endl;
   cout << endl;

   output(initialState, finalStates, totalStates, dfaSymbols);

   printf("transitions size = %d\n", transitions.size());
   for(tit = transitions.begin(); tit != transitions.end(); tit++) {
      cout << "Symbol: " << tit->first << " State:" << tit->second << endl;
   }

   printf("tmpStates/tmpSymbol\n");
   for(i = 0; i < tmpStates.size(); i++) {
      printf("tmpStates/tmpSymbols/curStates[%d] = %d/%s/%d\n", i, tmpStates[i], tmpSymbols[i].c_str(), curStates[i]);
   }

   vector <int> NFA;
   NFA.resize(totalStates);
   /*for (i = 0; i < tmpStates.size(); i++) {
      NFA[i].resize(totalStates);
   }*/

   vector <int> DFA;

   // Epsilon Closure Function
   vector <int> states;
   queue <int> stateStack;
   int state1;
   vector <int> epsilonStates;
   vector <int> closure;

   states.push_back(initialState);
   
   for (i = 0; i < states.size(); i++) {
      stateStack.push(states[i]);
   }

   for (i = 0; i < states.size(); i++) {
      closure.push_back(states[i]);
   }

   while (!stateStack.empty()) {
      state1 = stateStack.front();
      stateStack.pop();
      for (i = 0; i < tmpStates.size(); i++) {
         if (tmpSymbols[i] == "E") {
            epsilonStates.push_back(tmpStates[i]);
         }
      }

      for (i = 0; i < epsilonStates.size(); i++) {
         for (i = 0; i < closure.size(); i++) {
            if (epsilonStates[i] != closure[i]) {
               //flag
               //check if it already exists
               closure.push_back(epsilonStates[i]);
               stateStack.push(epsilonStates[i]);
            }
         }
      }

      // Sort the closure list
      vector <int> finalClosure;
      //finalClosure = qsort(closure);

      // return finalClosure when inside epsilon function
   }


   //_dfa_init_state = Epsilon_Closure(states, tmpStates, tmpSymbols, curStates);
   
   return 0;
}

/*vector <int> Epsilon_Closure(vector <int> states, vector <int> tmpStates, vector <string> tmpSymbols, vector <int> curStates) {

   vector <int> finalClosure;
   stack <int> stateStack;

   for t in T:
      stateStack.
   return finalClosure;
}*/
