// ZodiacTest.java
// Mitchell Wade
// January 15th, 2015
//
// This program
public class ZodiacTest {
    
    public ZodiacTest(String args[]) {

        // Creates a instance of the ChineseZodiac obj.
        ChineseZodiac year = ChineseZodiac.RABBIT;
        ChineseZodiac z;

        // Output the first Zodiac and respective year
        System.out.println("The last year of the " + year + " occurred in " + year.getYear());
        
                // Output the remaining Zodiacs and respective year
                for (z : ChineseZodiac.values()) {
                    System.out.println("The year of the " + z + " last occurred in " + z.getYear());
                }
    }
    
    public static void main (String args[]) {
        new ZodiacTest(args);
    }
}
