// SliderApp.java
// Mitchell Wade
// Mar. 5, 2015

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;

public class SliderApp {

    int minValue, maxValue, currentValue, incrementValue;
    JLabel valueLabel = new JLabel("Value:");
    JLabel sliderValue = new JLabel("");
    JSlider slider;
    JButton incrButton = new JButton("Increment");
    JButton decrButton = new JButton("Decrement");

    // Create the GUI and show it
    void createAndShowGUI() {

        // Make sure we have nice window decorations
        JFrame.setDefaultLookAndFeelDecorated(true);
        
        // Create the window
        JFrame frame = new JFrame("SliderApp");
        JPanel contentPane = (JPanel)frame.getContentPane();

        // Set up the window
        contentPane.setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Create panels
        JPanel sliderView = createSliderView();
        JPanel textView = createTextView();

        // Add objects to panels
        contentPane.add(textView, BorderLayout.NORTH);
        contentPane.add(sliderView, BorderLayout.CENTER);
        BorderLayout layoutMgr = (BorderLayout)contentPane.getLayout();
        layoutMgr.setVgap(20);

        // Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    // Crates the slider
    JPanel createSliderView() {
        JPanel sliderPanel = new JPanel();
        slider = new JSlider(minValue, maxValue, currentValue);

        // Add objects the slider
        sliderPanel.setLayout(new BorderLayout(10, 10));
        sliderPanel.add(incrButton, BorderLayout.LINE_END);
        sliderPanel.add(decrButton, BorderLayout.LINE_START);
        sliderPanel.add(slider, BorderLayout.CENTER);

        // Error message for inc
        incrButton.addActionListener(new ActionListener() {

                public void actionPerformed(ActionEvent e) {
                    if (!increment()) {
                    JOptionPane.showMessageDialog(incrButton,
                        "Cannot increment the value any futher",
                        "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
        });

        // Error message for dec
        decrButton.addActionListener(new ActionListener() {
                
                public void actionPerformed(ActionEvent e) {
                    if (!decrement()) {
                    JOptionPane.showMessageDialog(decrButton,
                        "Cannot decrement the value any futher",
                        "Error", JOptionPane.ERROR_MESSAGE);
                    }       
                }
        });

        slider.addChangeListener(new ChangeListener() {
                
                public void stateChanged(ChangeEvent e) {
                    JSlider s = (JSlider)e.getSource();
                    setCurrentValue(s.getValue());
                }
        });

        return sliderPanel;
    }

    JPanel createTextView() {
        
        JPanel textPanel = new JPanel();
        setSliderValue(currentValue);
        textPanel.setLayout(new FlowLayout());
        textPanel.add(valueLabel);
        textPanel.add(sliderValue);

        return textPanel;
    }

    boolean increment() {

        int newValue;

        if (currentValue == maxValue) return false;

        newValue = currentValue + incrementValue;

        if (newValue > maxValue) newValue = maxValue;

        setCurrentValue(newValue);

        return true;
    }

    boolean decrement() {

        int newValue;

        if (currentValue == minValue) return false;

        newValue = currentValue - incrementValue;

        if (newValue < minValue) newValue = minValue;

        setCurrentValue(newValue);

        return true;
    }

    void setCurrentValue(int newValue) {
        currentValue = newValue;
        setSliderValue(newValue);
        slider.setValue(newValue);
    }

    // Set the slider value
    void setSliderValue(int newValue) {
        sliderValue.setText(Integer.toString(currentValue));
    }

    public static void main(String[] args) {
        new SliderApp(args);
    }

    public SliderApp(String [] args) {

        // Check for proper usage
        if (args.length != 4) {
            System.err.println("usage: java SliderApp min max initialValue incrementValue");
            System.exit(1);
        }

        // Catch improper values from stdin
        try {
            minValue = Integer.parseInt(args[0]);
            maxValue = Integer.parseInt(args[1]);
            currentValue = Integer.parseInt(args[2]);
            incrementValue = Integer.parseInt(args[3]);
        }
        catch (NumberFormatException e) {
            System.out.println(e.getMessage() + " should be an integer");
            System.exit(1);
        }

        // Create and run the GUI
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                    createAndShowGUI();
                }
        });
    }
}
