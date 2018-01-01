// Rectangle.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.awt.*;

public class Rectangle extends GraphicalObject {

    // Zero argument constructor
    public Rectangle() { 
        super(); 
    }

    // Sets properties based on arguments
    public Rectangle(int l, int t, int w, int h, Color fc) {
        super(l, t, w, h, fc);
    }

    public void draw(Graphics g) {
        g.setColor(fillColor);
        g.fillRect(left, top, width, height);
    }

    public String toString() {
        return String.format("Rectangle(%d, %d, %d, %d)", left, top, width,
               height);
    }
}
