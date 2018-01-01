import Stack.*;
import java.util.Scanner;

class StackDriver {
    public static void main(String args[]) {
	Stack<String> myStack = new Stack<String>(5);
	Stack<String> defaultStack = new Stack<String>();

	Scanner console = new Scanner(System.in);
	Scanner lineTokenizer;
	
	while (console.hasNextLine()) {
	    lineTokenizer = new Scanner(console.nextLine());
	    String cmd = lineTokenizer.next();
	    if (cmd.equals("push")) {
		String value = lineTokenizer.next();
		if (!myStack.push(value)) {
		    System.out.printf("*** Error: Stack full. Cannot push %s onto stack\n", value);
	  	};
	    }
	    else if (cmd.equals("pop")) {
		String value = myStack.pop();
		defaultStack.push(value);
		System.out.println("popped value = " + value);
	    }
	    else 
		System.out.println("bad command: " + cmd);
	    lineTokenizer.close();
	}
	 
	// print the contents of the two stacks
	System.out.println("*** contents of myStack ***");
	while (!myStack.isEmpty()) 
	    System.out.println(myStack.pop());
	System.out.println("*** contents of defaultStack ***");
	while (!defaultStack.isEmpty()) 
	    System.out.println(defaultStack.pop());
    }
}
