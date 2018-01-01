// BoxLayoutDemo.java
// Mitchell Wade
// March 26, 2015
// This program creates a window application with 5 buttons and
// upon resizing the buttons certain buttons will stick to each
// side. Buttons 1-3 will go left and buttons 4-5 will go right.

/*
 * BoxLayoutDemo.java requires no other files.
*/

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import javax.swing.BoxLayout;
import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFrame;

public class BoxLayoutDemo {
    public static void addComponentsToPane(Container pane) {
        
        // Make the layout horizontal with X_AXIS
        pane.setLayout(new BoxLayout(pane, BoxLayout.X_AXIS));

        addAButton("Button 1", pane);

        // Add space between buttons
        pane.add(Box.createRigidArea(new Dimension(20, 0)));
       
        addAButton("Button 2", pane);
        
        // Add space between buttons
        pane.add(Box.createRigidArea(new Dimension(20, 0)));
        
        addAButton("Button 3", pane);
        
        // Add space between buttons
        pane.add(Box.createHorizontalGlue());
        
        addAButton("Long-Named Button 4", pane);
        
        // Add space between buttons
        pane.add(Box.createRigidArea(new Dimension(20, 0)));
        
        addAButton("5", pane);
    }

    private static void addAButton(String text, Container container) {
        JButton button = new JButton(text);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
        container.add(button);
    }

    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Create and set up the window.
        JFrame frame = new JFrame("BoxLayoutDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Set up the content pane.
        addComponentsToPane(frame.getContentPane());

        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
}
