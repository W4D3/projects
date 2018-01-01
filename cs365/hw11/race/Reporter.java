// Reporter.java
// Mitchell Wade
// April 25, 2015

package race;

class Reporter extends Thread {

    TimeKeeper scoreboard;
    int i = 0;
    int seconds = 0;

    public Reporter(TimeKeeper tk) {
        this.scoreboard = tk;
    }

    public void run() {
        while (!this.scoreboard.raceFinished()) {
            
            try {
                // Sleep for 2 seconds
                Thread.sleep(2000);
            }
            catch (InterruptedException e) {}
            
            i += 2000;

            seconds = i/1000;

            System.out.println("");
            System.out.println("Results after " + seconds + " seconds");

            this.scoreboard.printScoreboard();
        }
        this.scoreboard.printResults();
    }
}
