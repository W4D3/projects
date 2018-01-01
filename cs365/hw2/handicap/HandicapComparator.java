// HandicapComparator.java
// Mitchell Wade
// January 28th, 2015

import java.util.*;

public class HandicapComparator implements Comparator<Map.Entry<Double,String>> {
    public int compare(Map.Entry<Double,String> g1, Map.Entry<Double,String> g2) {
        Double h1 = g1.getKey();
        Double h2 = g2.getKey();
        return h1.compareTo(h2);
    }

}
