// Oval.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.awt.*;

public class Oval extends GraphicalObject {

    // Zero argument constructor
    public Oval() { 
        super(); 
    }

    // Sets properties based on arguments
    public Oval(int l, int t, int w, int h, Color fc) {
        super(l, t, w, h, fc);
    }

    public void draw(Graphics g) {
        g.setColor(fillColor);
        g.fillOval(left, top, width, height);
    }

    public String toString() {
        return String.format("Oval(%d, %d, %d, %d)", left, top, width, height);
    }
}
