// SumLines.java
// Mitchell Wade
// Feb. 26, 2015

import java.util.*;
import java.io.File;

/** This class illustrates exception handling. It reads lines
    from a file and sums the numbers on those lines. It handles
    two types of exceptions:
    1) FileNotFoundException: If the file entered on the command
       line does not exist, then a catch statement inside the
       while loop prompts the user for another file name and keeps
       doing so until the user enters a valid one.
    2) BadNumberException: This exception is user-defined and
       is thrown when a non-positive integer is read. It is handled
       by printing the bad number and an error message.
**/

class SumLines {
    public static void main(String args[]) throws java.io.FileNotFoundException {
        SumLines sum = new SumLines();
        String filename = args[0];

        while (true) {
            try {
                sum.execute(filename);
                break;
            }
            catch (java.io.FileNotFoundException e) {
                System.out.printf("Error: file %s not found%n", filename);
                System.out.printf("Enter a new file name: ");
                Scanner input = new Scanner(System.in);
                filename = input.next();
            }
        }
    }

    public void execute(String filename) throws java.io.FileNotFoundException {
        Scanner input = new Scanner(new File(filename));
        while (input.hasNextLine()) {
            Scanner line = new Scanner(input.nextLine());
            int sum = 0;
            while (line.hasNext()) {
                try {
                    int nextNum = line.nextInt();
                    if (nextNum <= 0) throw new BadNumberException(nextNum);
                    sum += nextNum;
                }
                catch(BadNumberException e) {
                    System.out.println(e);
                }
                catch(java.util.InputMismatchException e) {
                    System.out.println("Error: bad input value " + line.next() + " must be a positive integer");
                }
            }
            System.out.println("Sum = " + sum);
            line.close();
        }
    }
}
