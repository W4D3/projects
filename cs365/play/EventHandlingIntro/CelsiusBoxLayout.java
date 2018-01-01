import javax.swing.*;
import java.awt.event.*;
import javax.swing.border.*;
import java.awt.*;

public class CelsiusBoxLayout {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("CelsiusBoxLayout");
	JPanel contentPane = (JPanel)frame.getContentPane();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add the ubiquitous "Hello World" label.
        JLabel celsiusLabel = new JLabel("Celsius");
	JLabel fahrenheitLabel = new JLabel("Fahrenheit");
	fahrenheitLabel.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 10));

	JTextField celsiusValue = new JTextField();
	JButton converterButton = new JButton("Convert");

	//Parse degrees Celsius as a double and convert to Fahrenheit.
	converterButton.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    int tempFahr = (int)((Double.parseDouble(celsiusValue.getText()))
					 * 1.8 + 32);
		    fahrenheitLabel.setText(tempFahr + " Fahrenheit");
		    fahrenheitLabel.revalidate();
		    frame.pack();
		}
	    });

	Box celsiusBox = Box.createHorizontalBox();
	Box fahrenheightBox = Box.createHorizontalBox();
	/*
	converterButton.setMaximumSize(new Dimension(short.MAX_VALUE, short.MAX_VALUE));
	celsiusValue.setMaximumSize(new Dimension(short.MAX_VALUE, 
	*/
	celsiusBox.add(celsiusValue);
	celsiusBox.add(Box.createHorizontalGlue());
	celsiusBox.add(celsiusLabel);
	fahrenheightBox.add(converterButton);
	fahrenheightBox.add(Box.createHorizontalGlue());
	fahrenheightBox.add(fahrenheitLabel);
	
	contentPane.add(celsiusBox, BorderLayout.NORTH);
	contentPane.add(fahrenheightBox, BorderLayout.SOUTH);

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
