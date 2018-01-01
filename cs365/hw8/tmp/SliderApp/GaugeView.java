package SliderApp;

// GaugeView.java
// Mitchell Wade
// March 26th, 2015

import javax.swing.*;          
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class GaugeView extends JPanel implements Slider2 {

    SliderModel model;
    int needleX, needleY;   // Endpoint of the needle
    int centerX, centerY;   // Center of the gauge

    boolean draggingNeedle = false;  // If the needle is being dragged

    public GaugeView(SliderModel m) {

        model = m;
        model.addView(this);
        setBorder(BorderFactory.createLineBorder(Color.black));

        // Event handling
        addMouseListener(new MouseAdapter() {
                public void mousePressed(MouseEvent e) {

                int xDist = e.getX() - needleX;
                int yDist = e.getY() - needleY;
                double distFromNeedle = Math.sqrt(xDist*xDist + yDist*yDist);
                
                if (distFromNeedle <= 10) {
                    draggingNeedle = true;
                }
                }

                public void mouseReleased(MouseEvent e) {
                    draggingNeedle = false;
                }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
                public void mouseDragged(MouseEvent e) {
                
                if (draggingNeedle) {
                
                // Computes the angle of the mouse cursor with respect
                // to the center of the circle
                
                int xDist = e.getX() - centerX;
                int yDist = centerY - e.getY();
                double radians = Math.atan2(yDist, xDist);
                double angle = Math.toDegrees(radians);
                int newValue = (int)((angle / 180) * (model.maxValue - model.minValue));
                
                model.setValue(newValue);
                }
                }
        });
    }

    public Dimension getPreferredSize() {
        return new Dimension(200, 100);
    }

    public void paintComponent(Graphics g) {
        
        super.paintComponent(g);
        Graphics copyG = g.create();

        // Computes the center of the gauge
        int diameter = Math.min(getWidth(), 2*getHeight());
        centerX = getWidth() / 2;
        centerY = getHeight(); // y point is at bottom of JPanel

        // Computes the upper left corner of the gauge
        int leftX = centerX - diameter / 2;
        int topY = centerY - diameter / 2;

        // Draw the gauge outline
        copyG.setColor(Color.ORANGE);
        copyG.fillArc(leftX, topY, diameter, diameter, 0, 180);

        // draw the needle by computing its angle and then computing its
        // endpoint
        int value = model.getCurrentValue();
        int minValue = model.getMinValue();
        int maxValue = model.getMaxValue();
        double angle = 180 * ((double)value - minValue) / (maxValue - minValue);
        double radians = Math.toRadians(angle);

        needleX = (int)(centerX + ((double)diameter)/2 * Math.cos(radians));
        needleY = (int)(centerY - ((double)diameter)/2 * Math.sin(radians));
        copyG.setColor(Color.BLUE);
        copyG.drawLine(centerX, centerY, needleX, needleY);

        copyG.dispose();
    }

    // Update the gauge
    public void changedValue(int oldValue) {
        repaint();
    }
}
