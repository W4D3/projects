// Race.java
// Mitchell Wade
// April 25, 2015

package race;

class Race {
    
    public static void main(String[] args) {

        int contestants = 0, i = 0;
        TimeKeeper tk;
        
        if (args.length != 1) {
            System.err.println("Usage: java race numContestants");
            System.exit(1);
        }
        
        try {
            contestants = Integer.parseInt(args[0]);
        }
        catch (NumberFormatException e) {
            System.out.println("number of contestants must be an integer");
            System.exit(1);
        }

        tk = new TimeKeeper(contestants);
        
        System.out.println("Start the race!");
        
        for (i = 0; i < contestants; i++) {
            (new Thread(new Contestant(i+1, tk))).start();
        }

        (new Thread(new Reporter(tk))).start();
    }
}
