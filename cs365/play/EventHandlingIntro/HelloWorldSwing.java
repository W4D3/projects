import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;

public class HelloWorldSwing {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("HelloWorldSwing");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add the ubiquitous "Hello World" label.
        JLabel label = new JLabel("Hello World");
	label.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        frame.getContentPane().add(label);

        JLabel west = new JLabel("west");
	west.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        frame.getContentPane().add(west, BorderLayout.WEST);

        JLabel north = new JLabel("north");
	north.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        frame.getContentPane().add(north, BorderLayout.NORTH);

        JLabel east = new JLabel("east");
	east.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        frame.getContentPane().add(east, BorderLayout.EAST);

        JLabel south = new JLabel("south");
	south.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        frame.getContentPane().add(south, BorderLayout.SOUTH);


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
