import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

// Creates a JFrame window and animates a square moving across it, bouncing off the window edges.
// The square's color changes over time, varying from white to black and back again.
public class DrawChangingSquare extends JFrame {

    // dimensions of window (px)
    private static final int SCREEN_W = 300, SCREEN_H = 300;
    // number of ms to delay between redrawing the window
    private static final int DELAY = 33;

    private int square_x = 40;  // top-left x-coordinate of square
    private int square_w = 50;  // width of each square edge (px)
    private int speed_x = 5;  // amount to add to square_x each frame
    private int color_int = 0;  // integer to be used in each RGB color channel
    private int color_change = 5;  // amount to add/subtract to color_int each frame (higher = faster change)

    // constructor initializes the JFrame and sets it to display
    public DrawChangingSquare() {
        setSize(new Dimension(SCREEN_W, SCREEN_H));  // set size of window to SCREEN_W x SCREEN_H pixels
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);  // exit program on window close
        setTitle("Animation Example");  // set screen title
        setVisible(true);  // show the window

        // create a timer to redraw the window every DELAY milliseconds. This uses an ActionListener
        // that will call actionPerformed repeatedly. Inside actionPerformed we update animation logic,
        // then repaint the window. More logic could be put into this method if we so wished.
        Timer timer = new Timer(DELAY, new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                update();  // update position of square
                repaint();  // repaint the screen
            }
        });
        timer.start();
    }

    // updates the square's position and color each frame to create animation over time
    public void update() {
        // increment x-coordinate
        square_x += speed_x;

        // check if we've hit the right edge of the canvas
        if (square_x + square_w > SCREEN_W) {
            square_x = SCREEN_W - square_w;  // set to edge
            speed_x *= -1;  // reverse speed
        } else if (square_x < 0) {  // check if we've hit the left edge of the canvas
            square_x = 0;  // set to edge
            speed_x *= -1;  // reverse speed
        }

        // increment color_int
        color_int += color_change;

        // check color bounds (must be from 0-255)
        if (color_int > 255) {
            color_change *= -1;  // reverse color change direction
            color_int = 255;  // set to 255 (upper bound)
        } else if (color_int < 0) {
            color_change *= -1;  // reverse color change direction
            color_int = 0;  // set to 0 (lower bound)
        }
    }

    @Override // code to draw (paint) the window square to the canvas.
    public void paint(Graphics g) {
        g.setColor(Color.WHITE);  // set color to white
        g.fillRect(0, 0, SCREEN_W, SCREEN_H); // reset the window by drawing over it with white
        g.setColor(new Color(255, color_int, color_int));  // set color: all three channels are color_int
        g.fillRect(square_x, 50, square_w, square_w);  // draw square with correct coordinate and width/height
    }
}