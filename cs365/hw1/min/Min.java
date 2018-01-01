// Min.java
// Mitchell Wade
// January 20th, 2015
// This program takes a stream of input from the cmd 
// line and prints out the lowest value.

class Min {
    public Min(String args[]) {

        String minString = args[0];

        for (String element : args) {
            if (element.compareTo(minString) < 0)
                minString = element;
            }
            System.out.println(minString);
        }

        
    
    public static void main(String args[]) {
        new Min(args);
    }
}
