// GraphicsDriver.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.util.LinkedList;
import java.util.ListIterator;
import java.util.HashMap;
import java.util.Scanner;
import javax.swing.*;
import java.awt.*;

class GraphicsDriver extends JPanel {
    HashMap<String, Color> colorMap = new HashMap<String, Color>();

    {
        colorMap.put("red", Color.red);
        colorMap.put("gray", Color.gray);
        colorMap.put("magenta", Color.magenta);
        colorMap.put("blue", Color.blue);
        colorMap.put("green", Color.green);
        colorMap.put("orange", Color.orange);
        colorMap.put("yellow", Color.yellow);
        colorMap.put("black", Color.black);
    }

    JFrame window = new JFrame();
    LinkedList<GraphicalObject> components = new LinkedList<GraphicalObject>();

    public Dimension getPreferredSize() {
        return new Dimension(800, 800);
    }

    public GraphicsDriver () {
        Scanner console = new Scanner(System.in);
        Scanner lineTokenizer;

        while (console.hasNextLine()) {
            lineTokenizer = new Scanner(console.nextLine());
            // determine if the line has a name field
            if (lineTokenizer.hasNext()) {
                String objectName = lineTokenizer.next();
                if (objectName.equals("rectangle") ||
                        objectName.equals("oval")) {
                    int left = lineTokenizer.nextInt();
                    int top = lineTokenizer.nextInt();
                    int width = lineTokenizer.nextInt();
                    int height = lineTokenizer.nextInt();
                    String color = lineTokenizer.next();
                    Color c = colorMap.get(color);
                    if (objectName.equals("rectangle")) 
                        components.add(new Rectangle(left, top, width, height, c));
                    else
                        components.add(new Oval(left, top, width, height, c));
                }
                else if (objectName.equals("text")) {
                    int left = lineTokenizer.nextInt();
                    int top = lineTokenizer.nextInt();
                    String color = lineTokenizer.next();
                    Color c = colorMap.get(color);
                    String label = lineTokenizer.nextLine();
                    components.add(new Text(left, top, c, label));
                }
                else if (objectName.equals("roundtangle")) {
                    int left = lineTokenizer.nextInt();
                    int top = lineTokenizer.nextInt();
                    int width = lineTokenizer.nextInt();
                    int height = lineTokenizer.nextInt();
                    String color = lineTokenizer.next();
                    int arcsize;
                    if (lineTokenizer.hasNextInt())
                        arcsize = lineTokenizer.nextInt();
                    else {
                        String size = lineTokenizer.next();
                        if (size.equals("SMALL"))
                            arcsize = Roundtangle.SMALL;
                        else if (size.equals("MEDIUM"))
                            arcsize = Roundtangle.MEDIUM;
                        else
                            arcsize = Roundtangle.LARGE;
                    }
                    Color c = colorMap.get(color);
                    components.add(new Roundtangle(left, top, width, height,
                                c, arcsize));
                }
                else if (objectName.equals("line")) {
                    int x1 = lineTokenizer.nextInt();
                    int y1 = lineTokenizer.nextInt();
                    int x2 = lineTokenizer.nextInt();
                    int y2 = lineTokenizer.nextInt();
                    String color = lineTokenizer.next();
                    Color c = colorMap.get(color);
                    components.add(new Line(x1, y1, x2, y2, c));
                }
                else if (objectName.equals("end")) {
                    // time to read some points from the user
                    lineTokenizer.close();
                    break;
                }
                else {
                    System.out.println("invalid object name: must be one of (rectangle, roundtangle, line, oval, text)");
                    lineTokenizer.close();
                    continue;
                }
            }
            lineTokenizer.close();
        }    

        // get mouse points from user and find which object contains them
        pointCheck(console); 

        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.getContentPane().add(this, BorderLayout.CENTER); 
        window.pack(); 
        window.setVisible(true); 
    }

    void pointCheck(Scanner console) {
        ListIterator<GraphicalObject> iter;
        boolean foundObj = false;
        while (console.hasNextLine()) {
            Scanner lineTokenizer = new Scanner(console.nextLine());
            int x = lineTokenizer.nextInt();
            int y = lineTokenizer.nextInt();
            foundObj = false;
            for (iter = components.listIterator(components.size()); 
                    iter.hasPrevious();) {
                GraphicalObject obj = iter.previous();
                if (obj.containsPt(x, y)) {
                    System.out.printf("%s contains the point (%d, %d)%n",
                            obj, x, y);
                    foundObj = true;
                    break;
                }
            }
            if (!foundObj) {
                System.out.printf("No object contains the point (%d, %d)%n",
                        x, y);
            }
            lineTokenizer.close();
        }
    }

    static public void main(String args[]) {
        GraphicsDriver testDriver = new GraphicsDriver();
    }

    public void paintComponent(Graphics g) {
        for (GraphicalObject obj : components) {
            obj.draw(g);
        }
    }

}
