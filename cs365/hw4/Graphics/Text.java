// Text.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.awt.*;

public class Text extends GraphicalObject {

    String text = "";
    static final int HEIGHT = 16;
    static final int WIDTH = 7;

    // Zero argument constructor
    public Text() { 
        super(); 
    }

    // Sets properties based on arguments
    public Text(int l, int t, Color fc, String label) {
        super(l, t, WIDTH * label.length(), HEIGHT, fc);
        text = label;
    }

    String getText() { return text; }
    void setText(String s) { text = s; }

    public void draw(Graphics g) {
        g.setColor(fillColor);
        g.drawString(text, left, top);
    }

    public String toString() {
        return String.format("Text(%d, %d, %d, %d)", left, top, width,
                height);
    }
}
