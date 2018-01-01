// Salary.java
// Mitchell Wade
// January 27th, 2015
// This program determines whether or not each person in
// a group of persons is above or below the average salary
// for the group. The input will be n pairs of strings and
// salaries representing the names of each person and their
// salary.

import java.util.*;

class Salary {

    // Global variable to store average salary
    double avg = 0;

    // Person class to store data
    class Person {

        String name;
        double salary; 
        void Print() {
            System.out.printf("%-15s %,10.2f %b%n", name, salary, salary > avg);
        }

    }

    // use a list

    public Salary(String args[]) {
        
        // Stores person information
        double salary = 0, total = 0;
        String name;
        Person p;

        ArrayList<Person> l = new ArrayList<Person>();

        // Read in persons name and salary
        Scanner sc = new Scanner(System.in);
        
        while (sc.hasNextLine()) {
            
            // Create a new scanner and an instance of a person class 
            // for each element of the searchList
            Scanner lineTokenizer = new Scanner(sc.nextLine());
            p = new Person();

            // Parse person name and store in searchList
            name = lineTokenizer.next();
            p.name = name;
            
            // Parse person salary and store in searchList
            salary = lineTokenizer.nextDouble();
            p.salary = salary;

            // Calculate the average
            total += p.salary;

            // Add person to the list
            l.add(p);

            // Close the scanner for each person
            lineTokenizer.close();
        }

        // Calculate the average salary for the group
        avg = total / l.size();
        
        // Print out the average salary
        System.out.printf("average salary = %-,10.2f%n%n", avg);

        // Print the group and true or false if it is above the salary
        for (Person per : l) {
            per.Print();
        }

        //Close the scanner from stdin
        sc.close();
    }

    public static void main(String args[]) {
        new Salary(args);
    }
}

