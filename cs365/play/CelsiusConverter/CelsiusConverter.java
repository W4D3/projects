import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;

public class CelsiusConverter {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("CelsiusConvertor");
        JPanel contentPane = (JPanel)frame.getContentPane();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel celsiusLabel = new JLabel("Celsius");
        JLabel fahrenheitLabel = new JLabel("Fahrenheit");
        fahrenheitLabel.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 10));

        JTextField celsiusValue = new JTextField();
        JButton converterButton = new JButton("Convert");

        contentPane.setLayout(new GridLayout(2, 2, 5, 5));

        converterButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int tempFahr = (int)((Double.parseDouble(celsiusValue.getText())) * 1.8 + 32);
                fahrenheitLabel.setText(tempFahr + "Fahrenheit");
                frame.pack();

        contentPane.add(celsiusValue);
        contentPane.add(celsiusLabel);
        contentPane.add(converterButton);
        contentPane.add(fahrenheitLabel);

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
