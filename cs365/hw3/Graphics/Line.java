// Line.java
// Mitchell Wade
// Feb. 3, 2015

import java.awt.*;
import java.awt.geom.*;

public class Line extends GraphicalObject {

    int x1 = 0, y1 = 0, x2 = 20, y2 = 20;

    // Constant variable for containment range of a point on a line
    static final int range = 5;

    // Temporaty variable for managing points on a line
    protected static Line2D boundary = new Line2D.Double();

    // Zero argument constructor
    public Line() { 
        super();
        setBoundingBox();
    }

    // Sets properties based on arguments
    public Line(int xBegin, int yBegin, int xEnd, int yEnd, Color fc) {
        super();
        fillColor = fc;
        x1 = xBegin;
        x2 = xEnd;
        y1 = yBegin;
        y2 = yEnd;
        setBoundingBox();
    }

    // Calculates the boundary of the line
    public void setBoundingBox() {
        setLeft(Math.min(x1, x2));
        setTop(Math.min(y1, y2));
        setWidth(Math.abs(x1 - x2));
        setHeight(height = Math.abs(y1 - y2));
    }

    public int getX1() { return x1; }
    public void setX1(int x) { x1 = x; }
    
    public int getX2() { return x2; }
    public void setX2(int x) { x2 = x; }

    public int getY1() { return y1; }
    public void setY1(int y) { y1 = y; }
    
    public int getY2() { return y2; }
    public void setY2(int y) { y2 = y; }

    public void draw(Graphics g) {
        g.setColor(fillColor);
        g.drawLine(x1, y1, x2, y2);
    }

    public boolean containsPt(int x, int y) {
        boundary.setLine(x1, y1, x2, y2);
        return (boundary.ptSegDist(x, y) <= range);
    }

    public String toString() {
        return String.format("Line(%d, %d, %d, %d)", x1, y1, x2, y2);
    }
}
