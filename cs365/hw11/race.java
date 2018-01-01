// race.java
// Mitchell Wade
// April 24, 2015
// This program simulates a race between threads. There is one thread
// for the reporting and another thread for keeping track of data, 
// seperate threads for each contestant in the race, and one main thread
// that creates them.

package race;

import java.util.Random;
import java.io.*;

public class race(int contestant) {
    public class synchronized Contestant {      // <--- probably dont have to synchronize the class declerations
        // thread variables
        // generate random numbers
        // call reporter
            // send report to central time keeper that it has
            //      finished a segmnet of the race and the time 
            //      for that segment
    }
    
    public class synchronized Reporter {
        // calls the print methods in the time keeping class
        // ~35:00 in video -delay messages printed to screen
    }
    
    public class synchronized TimeKeeper {
        // finish queue
        // cumulative time of each contestant
        // number of segments completed by each contestant
        // if the thread has reported a new seg. time since the last score report
        // time required by the contestant to complete the last segment
        // finish order of the contestants (order in which they
        //      were added into the queue)
        
        // compents to print scoreboard
            // contstant number
        // components to print finish queue
    }
    
    
    public static void main(String[] args) throw new IOException {
        
        int contestants;
        
        if (args.length < 2) {
            System.err.println("Usage: java race #-contestants");
            System.exit(1);
        }
        try {
            contestants = Integer.parseInt(args[0]);
        }
        catch (IOException e) {
            System.out.println("number of contestants must be an integer");
            System.exit(1);
        }

        ExecutorService pool = Executors.newFixedThreadPool(contestants);

        // Make a thread for each contestant
        for (int i : contestants) {
            //pool execute(new PrintMsg(i));
            new Contestant();

            pool.shutdown();
        }

        new race(contestants);
    }

    // time tracking variable for each thread
        // how long it sleeps
        // time between awake or not?

    // reporter instantiation
        // save each contestants last segment time
        // cumulative time to complete assignmnet
        // last segment 

    // time keeper instantiation

    // make contestant threads

    // detach threads

    // free memory

    // exit

}

///////////////////////////////////////////////////////////////////////////
// Contestant Threads
class Contestant extends Thread {

    int contestantNumber;
    TimeKeeper scoreboard;

    public Contestan(int tmp, TimeKeeper tk) {
        this.contestantNumber = tmp;
        this.scoreboard = tk;
    }

    public void run() {
        Random localRandom = new Random();
        for (int i = 1; i <= 4; i++) {
            num = ThreadLocalRandom.current().nextInt(1000, 8000);
            
            try {
                Thread.sleep(num);
            } catch (InterruptedException e) {}

            this.scoreboard.reportTime(this.contestantNumber, num);
        }
        this.scoreboard.reportFinish(this.contestantNumber);
    }
}
///////////////////////////////////////////////////////////////////////////

   // dont have to use syncronized if we use a volatile varible
   // volatile boolean joy = false;
   // implict synchronized methods
   // happens before methods to ensure memory inconsistency

    for (i = 0; i < 3; i++) {
        num = ThreadLocalRandom.current().nextInt(1000, 8000);
        //Random random = new Random();
        
        try {
            Thread.sleep(num);
            //Thread.sleep(random.nextInt(5000));
        } catch (InterruptedExcpetion e) {
           // notify reporter
           // add stats when finished with race
        }

        // ----.wait() and notify
        // check if condition has changed
        // maybe use notify all to check what threads have finished?

        // random number generator
        // sleep for that time
        // signal the reporting thread
            // add stats when finished
    }

    // close resources
    // exit
}

// TimeKeeper Class

import java.io.*;


class syncronized Contestant() {
{
    // join all threads

    while all threads still executing {
        // collect data
    }

    // close resources
    // exit
}
