# nfa2dfa.py
# Mitchell Wade
# CS461 - Compilers
# This program converts an NFA to its corresponding DFA using the construction
# algorithm.

import sys

# EPSILON CLOSURE FUNCTION
def epsilon_closure(T, NFA):
  stateStack = []
  
  for t in T:
    stateStack.append(t)

  closure = list(T)
  while stateStack:
    t = stateStack.pop()    #grab the next state
    epsilon_states = [x[1] for x in NFA[t] if x[0] == 'E'] #grab epsilon states
    print("epsilon_states\n")
    print(epsilon_states)
    for j in epsilon_states:
      if not j in closure:  #if its not there, add it
        closure.append(j)
        stateStack.append(j)

  finalClosure = tuple(sorted(closure))
  return finalClosure

# MOVE FUNCTION
def move(T, a, NFA):
  moveStates = set([])
  for n in T:
    stateIndex = [x[1] for x in NFA[n] if x[0] == a]
    moveStates.update(stateIndex)
  return tuple(moveStates)

# CREATES A NEW DFA STATE
def create_new_dfa_state(states, index, DFA, d2r, r2d):
  newState = index+1

  if r2d.has_key(states):
    print "error: raw DFA state already exists"
    print ("states: %s" % states), (" newState: %s" % newState)
    raise SystemExit(1)
  if d2r.has_key(newState):
    print "error: DFA state already exists"
    print ("states: %s" % states), (" newState: %s" % newState)
    raise SystemExit(1)

  r2d[states] = newState
  d2r[newState] = states
  DFA[newState] = []

  print "new DFA state: ", ("%d" % newState).ljust(3), " --> ", ("%s" % setstr(states))
  return newState

# CHECK STATE TABLE
def get_unmarked_state(DFA, mark):
  for dstate in DFA.keys():
    if not mark[dstate]:
      return dstate
  return None

# PRINTS NFA/DFA STATES AS SETS
def setstr(x):

  if not x:
    return "{}"

  ret = "{"
  for y in x[:-1]:
    ret += ("%d," % y)
  ret += "%d}" % x[-1]
  
  return ret

# MAIN FUNCTION
def nfa2dfa(args):

  print "reading NFA ...",
 
  # Read the NFA details from input file
  nfaInitialState = int(sys.stdin.readline().split()[2])
  nfaFinalStates = tuple([int(x) for x in sys.stdin.readline().split()[2].strip('{}').split(',')]) 
  nfaTotalStates = int(sys.stdin.readline().split()[2])
  nfaSymbols = sys.stdin.readline().split()[1:]
  dfaSymbols = [x for x in nfaSymbols if not x == 'E']

  NFA = {}
 
  # Create labeled pairs for the data
  for i in range(nfaTotalStates):  
    pts = sys.stdin.readline().split() 
    label = int(pts[0]) 
    transitions = [] 
    
    for j,tx in enumerate(pts[1:]): 
      if tx != '{}':
        s  = nfaSymbols[j] 
        tmp = set([int(x) for x in tx.strip('{}').split(',')])
        for x in tmp:
          transitions.append((s, x)) 
    
    NFA[label] = transitions 
  print "done."

  print "\ncreating corresponding DFA ..."
  DFA = {}
  d2r = {}
  r2d = {}
  currentStateDFA = 0
  print("NFA\n")
  print(NFA)
  print("\n")
  print("tuple([nfaInitialState])]\n")
  print tuple([nfaInitialState])
  print("\n")
  _dfa_init_state = epsilon_closure(tuple([nfaInitialState]), NFA)
  dfa_init_state = create_new_dfa_state(_dfa_init_state, currentStateDFA, DFA, d2r, r2d)
  currentStateDFA = dfa_init_state

  mark = {}
  mark[dfa_init_state] = False

  T = get_unmarked_state(DFA, mark)
  while T:
    mark[T] = True

    for sym in dfaSymbols:
      _U = epsilon_closure(move(d2r[T],sym,NFA), NFA)
      if _U:
        if not _U in r2d.keys():
          currentStateDFA = create_new_dfa_state(_U, currentStateDFA, DFA, d2r, r2d)
          mark[currentStateDFA] = False
        DFA[T].append((sym,r2d[_U]))

    T = get_unmarked_state(DFA, mark)

  dfa_final_states = tuple(sorted([x for x in DFA.keys()\
                       if any([ True if y in nfaFinalStates else False\
                              for y in d2r[x] ])]))
  print "done."
  print "\nfinal DFA:"

  auto = DFA
  init_state = dfa_init_state
  final_states = dfa_final_states
  symbols = dfaSymbols
  sorted_syms = sorted([x for x in symbols if not x == 'E'])
  if 'E' in symbols:
    sorted_syms.append('E')

  print "Initial State: ", ("%d" % init_state)
  print "Final States:  ", ("%s" % setstr(final_states))
  print "Total States:  ", ("%d" % len(auto.keys()))

  print "State".ljust(7),
  for sym in sorted_syms:
    print ("%s" % sym).ljust(16),
  print ""

  for state in sorted(auto.keys()):
    print ("%d" % state).ljust(7),
    for sym in sorted_syms:
      tmp = tuple(sorted([x[1] for x in auto[state] if x[0] == sym]))
      print ("%s" % setstr(tmp)).ljust(16),
    print ""

if __name__ == "__main__":
  nfa2dfa(sys.argv)
