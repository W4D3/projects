// TimeKeeper.java
// Mitchell Wade
// April 25, 2015

package race;

import java.util.Vector;

class TimeKeeper {

    class ContestantData {
        int numSegmentsCompleted = 0;
        int lastSegmentTime = 0;
        int contestantNumber;
        int totalTime = 0;
        boolean newStats = false;

        ContestantData(int num) {
            this.contestantNumber = num;
        }
    }

    Vector<ContestantData> finishQueue = new Vector<ContestantData>();
    Vector<ContestantData> contestants = new Vector<ContestantData>();

    // Initalize Structs
    public TimeKeeper(int num) { 
        
        int i;

        for (i = 0; i < num; i++) {
            this.contestants.add(new ContestantData(i + 1));
        }
    }

    // Update each contestants stats
    public void reportTime(int num1, int num2) {
        
        ((ContestantData)this.contestants.get(num1 - 1)).totalTime += num2;
        ((ContestantData)this.contestants.get(num1 - 1)).numSegmentsCompleted += 1;
        ((ContestantData)this.contestants.get(num1 - 1)).lastSegmentTime = num2;
        ((ContestantData)this.contestants.get(num1 - 1)).newStats = true;
    }

    // Add contestants to the queue if they finished a segment
    public synchronized void reportFinish(int num) {

        this.finishQueue.add(this.contestants.get(num-1));
    }

    // Check if all contestants have finished and 
    // trigger the final results to be printed
    public boolean raceFinished() { 
        
        return this.finishQueue.size() == this.contestants.size();
    }

    // Print race scoreboard
    public void printScoreboard() {

        int i;

        System.out.format("%10s %10s %5s %13s%n", new Object[] { "Contestant", "Segments", "Time", "Last Segment" });
        
        for (i = 0; i < this.contestants.size(); i++) {

            System.out.format("%10d %10d %5d", new Object[] { Integer.valueOf(i + 1), Integer.valueOf(
                ((ContestantData)this.contestants.get(i)).numSegmentsCompleted), 
                Integer.valueOf(((ContestantData)this.contestants.get(i)).totalTime) });
            
            if (((ContestantData)this.contestants.get(i)).newStats) {
                System.out.format(" %13d", new Object[] { Integer.valueOf(
                ((ContestantData)this.contestants.get(i)).lastSegmentTime) });
                
                ((ContestantData)this.contestants.get(i)).newStats = false;
            }

            System.out.format("%n", new Object[0]);
        }
    }

    // Print the final standings
    public void printResults() {

        System.out.format("%nFinal Results%n", new Object[0]);
        
        for (int i = 0; i < this.finishQueue.size(); i++) {
            System.out.format("%3d %5d%n", new Object[] { 
                Integer.valueOf(((ContestantData)this.finishQueue.get(i)).contestantNumber), 
                Integer.valueOf(((ContestantData)this.finishQueue.get(i)).totalTime) });
        }
    }
}

