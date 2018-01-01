// Handicap.java
// Mitchell Wade
// January 28th, 2015
//
// This program takes two files from stdin and calculates
// the handicap for golfers that were in the input. It uses
// a TreeMap to store the information for Golfers and a HashMap
// to store information for the Courses.

import java.util.*;
import java.io.*;

class Handicap {

    private TreeMap <String, Golfer> Golfers;       /* Stores golfers */
    private HashMap <String, Course> Courses;       /* Stores courses */
    private List <Map.Entry<Double, String>> HandicapList; /* Stores handicaps */

    // Stores information associated with each golfer
    class Golfer {
        
        String name;                                /* Stores golfer last name */
        TreeMap <GregorianCalendar, Double> scores; /* Stores golfer scores */
        public double handicap;                     /* Stores golfer handicap */

        // Calculates differentials
        public void addScore(GregorianCalendar date, int score, String course) {            
            double diff;

            Course c = Courses.get(course);
            diff = (score - c.rating) * 113 / c.slope;
            scores.put(date, diff);
        }

        // Calcultes and sets the handicap for each golfer
        public void computeHandicap() {
        
            double avg = 0;
            Set scoreSet = scores.entrySet();
            Iterator i = scoreSet.iterator();
            int count = 1;
            List <Double> lowest20 = new ArrayList<Double>();

            // Set players without 20 scores as invalid
            if(scores.size() < 20){
                handicap = 0;
                return;
            }

            // Grab the lowest 20 scores
            while(i.hasNext()){

                // Break after 20 scores
                if(count > 20) break;

                Map.Entry me = (Map.Entry)i.next();
                lowest20.add((Double)me.getValue());
                count++;
            }

            // Sort the lowest 20 scores
            Collections.sort(lowest20);
            
            // Add up the 20 lowest scores
            count = 1;
            for (Double s : lowest20){
                if(count > 10) break;
                avg += s;
                count++;
            }

            // Calculate the average and handicap
            avg /= 10;
            handicap = 0.96 * avg;

        }
    }

    // Stores information associated with each course
    class Course {

        String name;
        double slope;
        double rating;
    }

    // Reads in the score file from the cmd line
    private void readScoreFile(String sf) throws IOException {

        int count = 0, month = -1, day = -1, year = -1, score = -1;
        Golfer g = null;
        Scanner input_reader;
        String name = "";
        String course = "";
        String line = "";

        input_reader = new Scanner(new BufferedReader(new FileReader(sf)));

        // Read in the input
        while(input_reader.hasNextLine()){

            line = input_reader.nextLine();
            Scanner tokenizer = new Scanner(line);

            // Break out of while loop if out of input
            if(!tokenizer.hasNext()) continue;

            // Reset values
            course = "";
            count = 0;

            // Set input based on type
            while(tokenizer.hasNext()){

                switch(count){
                    case 0:
                        month = tokenizer.nextInt();
                        break;
                    case 1:
                        day = tokenizer.nextInt();
                        break;
                    case 2:
                        year = tokenizer.nextInt();
                        break;
                    case 3:
                        name = tokenizer.next();
                        break;
                    case 4:
                        score = tokenizer.nextInt();
                        break;
                    default:
                        if(course.length() == 0){
                            course = tokenizer.next();
                        } else {
                            course = course + " " + tokenizer.next();
                        }
                        break;
                }
                count++;
            }

            tokenizer.close();

            // Check if the golfer already exists
            if(Golfers.containsKey(name)){
                g = Golfers.get(name);
            } else {

                // Create a new golfer
                g = new Golfer();
                g.name = name;
                g.scores = new TreeMap <GregorianCalendar, Double> (Collections.reverseOrder());
                Golfers.put(g.name, g);
            }
            g.addScore(new GregorianCalendar(year, month-1, day), score, course);

        }

        input_reader.close();

    }

    // Reads in the course file from the cmd line
    private void readCourseFile(String cf) throws IOException {

        String line;
        Scanner input_reader;
        int count;
        Course c = null;
        String s;

        input_reader = new Scanner( new BufferedReader( new FileReader(cf) ) );

        // Read in input
        while(input_reader.hasNextLine()){
            line = input_reader.nextLine();

            Scanner tokenizer = new Scanner(line);

            // Check for the end of input
            if(!tokenizer.hasNext()) continue;
            s = tokenizer.next();

            // Set course
            if(s.equals("Course")){
                count = 0;
                c = new Course();
                while(tokenizer.hasNext()){
                    if(count == 0){
                        c.name = tokenizer.next();
                        count++;
                    } else {
                        c.name = c.name + " " + tokenizer.next();
                    }
                }
            }

            // Set rating
            if(s.equals("Rating")){
                c.rating = tokenizer.nextDouble();
                s = tokenizer.next();
                c.slope = tokenizer.nextInt();
                Courses.put(c.name, c);
            }

            tokenizer.close();
        }

        input_reader.close();
    }

    public Handicap (String args[]) throws IOException {

        Golfer g = null;
        Golfers = new TreeMap<String, Golfer>();
        Courses = new HashMap<String, Course>();

        // Read in the input
        readCourseFile(args[1]);
        readScoreFile(args[0]);

        // Create a list for the handicap scores
        HandicapList = new ArrayList<Map.Entry<Double, String>>();
        Set golferSet = Golfers.entrySet();
        Iterator i = golferSet.iterator();

        // Read in all golfers
        while (i.hasNext()) {
            Map.Entry me = (Map.Entry)i.next();
            g = Golfers.get(me.getKey());
            g.computeHandicap();
            HandicapList.add(new AbstractMap.SimpleEntry<Double, String>(g.handicap, g.name));
        }

        // Compare values
        Collections.sort(HandicapList, new HandicapComparator());

        // Print out golfers and their handicap
        for (Map.Entry<Double, String> handicaps : HandicapList) {
            System.out.printf("%5.2f %s%n", handicaps.getKey(), handicaps.getValue());
        }

    }

    public static void main(String args[]) throws IOException {
        new Handicap(args);
    }
}
