import javax.swing.*;
import java.awt.*;

// Creates a JFrame window and draws a Blue square to it
public class DrawSquare extends JFrame {

    // custom RGB-color used to draw the square
    private static final Color BLUE = new Color(66, 122, 244);
    // dimensions of window (px)
    private static final int SCREEN_W = 300, SCREEN_H = 300;

    // constructor initializes the JFrame and sets it to display
    public DrawSquare() {
        setSize(new Dimension(SCREEN_W, SCREEN_H));  // set size of window to SCREEN_W * SCREEN_H pixels
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);  // exit program on window close
        setTitle("Animation Example");  // set window title
        setVisible(true);  // show the window
    }

    @Override // code to draw (paint) the window square to the canvas. Called when the window is displayed.
    // Will not be called again unless the window has to be redrawn.
    public void paint(Graphics g) {
        g.setColor(BLUE);  // set color to be used for drawing calls
        g.fillRect(50, 50, 50, 50);  // draw square with top-left coordinate at (50, 50) and width/height of 50 px
    }
}