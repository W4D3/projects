// Roundtangle.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.awt.*;

public class Roundtangle extends Rectangle {

    public static final int SMALL = 10;
    public static final int MEDIUM = 20;
    public static final int LARGE = 30;
    int arc = MEDIUM; // Sets the default to medium

    // Zero argument constructor
    public Roundtangle() { 
        super(); 
    }

    // Sets properties based on arguments
    public Roundtangle(int l, int t, int w, int h, Color fc, int a) {
        super(l, t, w, h, fc);
        arc = a;
        fillColor = fc;
    }

    public int getArcSize() { return arc; }
    public void setArcSize(int a) { arc = a; }

    public void draw(Graphics g) {
        g.setColor(fillColor);
        g.fillRoundRect(left, top, width, height, arc, arc);
    }

    public String toString() {
        return String.format("Roundtangle(%d, %d, %d, %d)", left, top,
                width, height);
    }
}
