package SliderApp;

// SliderView.java
// Mitchell Wade
// March 26, 2015

import javax.swing.*;          
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class SliderView extends JPanel implements Slider2 {

    // Create the slider
    JSlider slider;

    // Initalize the buttons
    JButton incrButton = new JButton("Increment");
    JButton decrButton = new JButton("Decrement");
    
    // Create the model
    SliderModel model;

    public SliderView(SliderModel m) {

        // Grab the model and create the view
        model = m;
        model.addView(this);

        // Initialize the slider
        slider = new JSlider(model.getMinValue(), model.getMaxValue(), 
                model.getCurrentValue());

        // Add each view to the API
        this.setLayout(new BorderLayout(10, 10));
        this.add(incrButton, BorderLayout.LINE_END);
        this.add(decrButton, BorderLayout.LINE_START);
        this.add(slider, BorderLayout.CENTER);

        
        // Check for incrementation errors
        incrButton.addActionListener(new ActionListener() {
                
                public void actionPerformed(ActionEvent e) {
                    if (!model.increment()) {
                        JOptionPane.showMessageDialog(incrButton,
                        "Cannot further increment the value",
                        "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
        });
        
        // Check for decrementation errors
        decrButton.addActionListener(new ActionListener() {
                
                public void actionPerformed(ActionEvent e) {
                    if (!model.decrement()) {
                        JOptionPane.showMessageDialog(decrButton,
                        "Cannot further decrement the value",
                        "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
        });

        // Add ChangeLister to the slider
        slider.addChangeListener(new ChangeListener() {
                
                public void stateChanged(ChangeEvent e) {
                    JSlider s = (JSlider)e.getSource();
                    model.setValue(s.getValue());
                }
        });
    }

    // Update the value
    public void changedValue(int value) {
        slider.setValue(value);
    }
}
