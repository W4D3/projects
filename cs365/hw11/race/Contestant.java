// Contestant.java
// Mitchell Wade
// April 25, 2015

package race;

import java.util.Random;

class Contestant extends Thread {

    int contestantNumber;
    TimeKeeper scoreboard;

    public Contestant(int tmp, TimeKeeper tk) {
        this.contestantNumber = tmp;
        this.scoreboard = tk;
    }

    public void run() {
        
        int number;
        int low = 1000;
        int high = 8000;

        for (int i = 1; i <= 4; i++) {
            Random num = new Random();

            number = num.nextInt(high-low)+low;
            try {
                Thread.sleep(number);
            } catch (InterruptedException e) {}

            this.scoreboard.reportTime(this.contestantNumber, number);
        }
        this.scoreboard.reportFinish(this.contestantNumber);
    }
}
