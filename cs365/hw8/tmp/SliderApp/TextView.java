package SliderApp;

// TextView.java
// Mitchell Wade
// March 26, 2015

import javax.swing.*;          
import java.awt.event.*;

class TextView extends JLabel implements Slider2 {
    
    // Set the label
    String labelPrefix = "Value: ";
    
    // Create a new model
    SliderModel model;

    // Create and set the TextView
    TextView(SliderModel m) {

        // Initialize the view
        setText(labelPrefix + m.getCurrentValue());
        
        // Grab the model and add to the view
        model = m;
        model.addView(this);

        // Centers the view
        setHorizontalAlignment(JLabel.CENTER);
    }

    // Update the view
    public void changedValue(int value) {
        setText(labelPrefix + value);
    }
}
