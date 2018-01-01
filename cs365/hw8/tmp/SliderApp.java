package SliderApp;

// SliderApp.java
// Mitchell Wade
// March 26, 2015

import javax.swing.*;          
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class SliderApp {

    int minValue;
    int maxValue;
    int initialValue;
    int incrementValue;
    
    void createAndShowGUI() {

        // Create and set up the window 
        JFrame frame = new JFrame("SliderApp");
        JPanel contentPane = (JPanel)frame.getContentPane();

        // Empty border creates a nice spacing around the edge of the window
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        contentPane.setBorder(BorderFactory.createEmptyBorder(
                    20, //top
                    20, //left
                    20, //bottom
                    20) //right
                );

        // Creates the API's components
        SliderModel model = new SliderModel(minValue, maxValue, initialValue,
                incrementValue);
        SliderView slider = new SliderView(model);
        TextView text = new TextView(model);
        GaugeView gauge = new GaugeView(model);

        // Add views to window and add a Vgap between each
        contentPane.add(text, BorderLayout.NORTH);
        contentPane.add(slider, BorderLayout.CENTER);
        contentPane.add(gauge, BorderLayout.SOUTH);
        BorderLayout layoutMgr = (BorderLayout)contentPane.getLayout();
        layoutMgr.setVgap(20);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new SliderApp(args);
    }

    public SliderApp(String [] args) {
        
        // Usage
        if (args.length != 4) {
            System.err.println("usage: java SliderApp min max initialValue incrementValue");
            System.exit(1);
        }

        // Grab user input
        try {
            minValue = Integer.parseInt(args[0]);
            maxValue = Integer.parseInt(args[1]);
            initialValue = Integer.parseInt(args[2]);
            incrementValue = Integer.parseInt(args[3]);
        }
        // Check for user errors
        catch (NumberFormatException e) {
            System.out.println(e.getMessage() + "--should be an integer");
            System.exit(1);
        }

        // Schedules a job for the event-dispatching thread
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                createAndShowGUI();
                }
                });
    }
}
