// SalaryList.java
// Mitchell Wade
// January 20th, 2015
//
// This program determines whether or not each person in
// a group of persons is above or below the average salary
// for the group. The input will be n pairs of strings and
// salaries representing the names of each person and their
// salary. It uses a linked list as the data structure to 
// hold each individual salary and outputs the list in 
// ascending order by salary.

class SalaryList {
    class Person {
        String name;
        double salary;
        Person next;
        Person prev;

        Person(String n, double s) {
            name = n;
            salary = s;
            next = this;
            prev = this;
        }
    }

    // Creates the linked list
    Person createList(String args[]) {

        Person top = new Person("", 0);
        Person newPerson, nextPerson;
        
        for (int i = 0; i < args.length; i+=2) {

            newPerson = new Person(args[i], Double.parseDouble(args[i+1]));

            // Check the next persons salary
            for (nextPerson = top.next; nextPerson != top; nextPerson = nextPerson.next) {
                if (newPerson.salary < nextPerson.salary) 
                    break;
            }

            // Add the next person to the linked list
            Person prevPerson = nextPerson.prev;
            prevPerson.next = newPerson;
            newPerson.prev = prevPerson;
            newPerson.next = nextPerson;
            nextPerson.prev = newPerson;
        }
        return top;
    }

    public SalaryList(String args[]) {

        int numPeople;
        double avg = 0;
        Person nextPerson;
        
        // Check for a even number of arguments
        if ((args.length % 2) != 0)
            System.out.println("Input requires an even number of arguments");

        // Calculate the number of people
        numPeople = args.length/2;

        // Create the list
        Person searchList = createList(args);

        // Calculate the average salary
        for (nextPerson = searchList.next; nextPerson != searchList; nextPerson = nextPerson.next) {
            avg += nextPerson.salary;
        }

        avg = avg / numPeople;

        // Output the average salary
        System.out.printf("average salary = %-,10.2f%n%n", avg);
       
       // Print true or false if a person is over the average
       // and print their names in alpha. order
        for (nextPerson = searchList.next; nextPerson != searchList; nextPerson = nextPerson.next) {
            
            System.out.printf("%-15s %,10.2f %b%n", nextPerson.name, nextPerson.salary,
                nextPerson.salary > avg ? true : false);
        }
    }

    public static void main(String args[]) {
        new SalaryList(args);
    }

}
