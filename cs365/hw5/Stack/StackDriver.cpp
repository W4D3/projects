#include <iostream>
#include "Stack.h"

using namespace std;

int main() {
  Stack<string,5> myStack;
  Stack<string> defaultStack;
  string cmd, value;

  while (cin >> cmd) {
    if (cmd == "push") {
      cin >> value;
      if (!myStack.push(value)) {
	cout << "*** Error: Stack full. Cannot push " << value << " onto stack\n";
      }
    }
    else if (cmd == "pop") {
      value = myStack.pop();
      defaultStack.push(value);
      cout << "popped value = " << value << endl;
    }
    else 
      cout <<"bad command: " << cmd << endl;
  }
	 
  // print the contents of the two stacks
  cout << "*** contents of myStack ***" << endl;
  while (!myStack.isEmpty())
    cout << myStack.pop() << endl;

  cout << "*** contents of defaultStack ***" << endl;
  while (!defaultStack.isEmpty()) 
    cout << defaultStack.pop() << endl;
}
