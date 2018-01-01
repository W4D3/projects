// Salary.java
// Mitchell Wade
// January 20th, 2015
// This program determines whether or not each person in
// a group of people is above or below the average salary
// of that group. The input will be n pairs of strings and
// salaries representing the names of each person and their 
// salary. 

class Salary {
    class Person {
        String name;
        double salary;
    }

    public Salary(String args[]) {
        
        int i;
        double avg = 0;
        
        // Check for a even number of arguments
        if ((args.length % 2) != 0) {
            System.out.println("Input requires an even number of arguments%n");
            System.out.println("usage: name1 salary1 name2 salary2 ...");
        }

        // Allocates an array of person structs for the number of specified people
        Person searchList[] = new Person[args.length/2];

        // Populate the array
        for (i = 0; i < searchList.length; i++) {
            searchList[i] = new Person();
            searchList[i].name = args[2*i];
            searchList[i].salary = Double.parseDouble(args[2*i + 1]);
            avg += searchList[i].salary;
        }

        // Compute the average
        avg = avg / searchList.length;

        // Output the average salary
        System.out.printf("average salary = %-,10.2f%n%n", avg);

        // Print true or false if each person is over the average
        for (i = 0; i < searchList.length; i++) {
            System.out.printf("%-15s %,10.2f %b%n", searchList[i].name, searchList[i].salary,
                searchList[i].salary > avg ? true : false);
        }
    }

    public static void main(String args[]) {
        new Salary(args);
    }
}
