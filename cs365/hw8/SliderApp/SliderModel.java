package SliderApp;

// SliderModel.java
// Mitchell Wade
// March 26, 2015

import java.util.LinkedList;

class SliderModel {

    int increment;
    int currentValue;
    int minValue;
    int maxValue;

    // List for each view
    LinkedList <Slider2> views = new LinkedList <Slider2>();

    // Set up the slider model based on specified values
    SliderModel(int min, int max, int initialValue, int incr) {
        
        increment = incr;
        currentValue = initialValue;
        minValue = min;
        maxValue = max;
    }

    // Call constructors
    int getMinValue() { return minValue; }
    int getMaxValue() { return maxValue; }
    int getCurrentValue() { return currentValue; }
    int getIncrValue() { return increment; }

    
    // Set and check limits for the current value
    boolean setValue(int value) {
        
        if ((value < minValue) || (value > maxValue)) {
            return false;
        }
        
        currentValue = value;
        notifyViews();

        return true;
    }

    // Set and check limits for the maxValue
    boolean increment() {
        
        if (currentValue == maxValue) {
            return false;
        }

        currentValue = currentValue + increment;
        
        if (currentValue > maxValue) {
            currentValue = maxValue;
        }

        notifyViews();
        
        return true;
    }

    // Set and check limits for the minValue
    boolean decrement() {

        if (currentValue == minValue) {
            return false;
        }

        currentValue = currentValue - increment;
        
        if (currentValue < minValue) {
            currentValue = minValue;
        }

        notifyViews();
        
        return true;
    }

    // Shows each view
    void addView(Slider2 v) {
        views.add(v);
    }
    

    // Update each view of slider when changed by user
    void notifyViews() {
        for (Slider2 v : views) 
            v.changedValue(currentValue);
    }
}
