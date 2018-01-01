// GraphicalObject.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.awt.*;

public abstract class GraphicalObject {
    
    int left = 0, top = 0, width = 20, height = 20;
    Color fillColor = Color.BLACK; // Sets the default to black

    // Zero argument constructor
    public GraphicalObject() {}

    // Sets properties based on arguments
    public GraphicalObject(int l, int t, int w, int h, Color fc) {
        left = l;
        top = t;
        width = w;
        height = h;
        fillColor = fc;
    }

    public int getLeft() { return left; }
    public void setLeft(int l) { left = l; }
    
    public int getTop() { return top; }
    public void setTop(int t) { top = t; }
    
    public int getWidth() { return width; }
    public void setWidth(int w) { width = w; }
    
    public int getHeight() { return height; }
    public void setHeight(int h) { height = h; }
    
    public Color getFillColor() { return fillColor; }
    public void setFillColor(Color fc) { fillColor = fc; }

    abstract public void draw(Graphics g);
    
    public boolean containsPt(int x, int y) {

        if ((x >= left) && (x <= left + width) && (y >= top) &&
           (y <= top + height)) {
            return true;
        } else { return false; }
    }
}
