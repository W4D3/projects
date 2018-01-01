// ChineseZodiac.java
// Mitchell Wade
// January 15th, 2015
//
// This program declares an enumerated type called ChineseZodiac
// which are enumerated constants for a Chinese Zodiac. The getYear
// func. returns the year associated with the Zodiac it was passed.

public enum ChineseZodiac {
    
    RAT(2008),
    BULL(2009),
    TIGER(2010),
    RABBIT(2011),
    DRAGON(2012),
    SNAKE(2013),
    HORSE(2014),
    GOAT(2015),
    MONKEY(2004),
    COCK(2005),
    DOG(2006),
    PIG(2007);

    private final int lastYear;

    private ChineseZodiac(int lastYear) {
        this.lastYear = lastYear;
    }

    public int getYear() {
        return lastYear;
    }
}
