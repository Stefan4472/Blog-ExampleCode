import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

// Creates a JFrame window and animates a blue square moving across it
public class DrawMovingSquare extends JFrame {

    // custom RGB-color used to draw the square
    private static final Color GREEN = new Color(39, 100, 42);
    // dimensions of window (px)
    private static final int SCREEN_W = 300, SCREEN_H = 300;
    // number of ms to delay between redrawing the window
    private static final int DELAY = 33;
    // top-left x-coordinate of square
    private int square_x = 40;

    // constructor initializes the JFrame and sets it to display
    public DrawMovingSquare() {
        setSize(new Dimension(SCREEN_W, SCREEN_H));  // set size of window to SCREEN_W x SCREEN_H pixels
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);  // exit program on window close
        setTitle("Animation Example");  // set screen title
        setVisible(true);  // show the window

        // create a timer to redraw the window every DELAY milliseconds. This uses an ActionListener
        // that will call actionPerformed() repeatedly. Inside actionPerformed we update animation logic,
        // then repaint the window. We could put more updating logic in this method if we wanted to.
        Timer timer = new Timer(DELAY, new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                update();  // update position of square
                repaint();  // repaint the screen
            }
        });
        // start the timer
        timer.start();
    }

    // updates the square's position between frames, adding 5 to the square's coordinate each call
    public void update() {
        square_x += 5;
    }

    @Override // code to draw (paint) the window
    public void paint(Graphics g) {
        g.setColor(Color.WHITE);  // set color to white
        g.fillRect(0, 0, SCREEN_W, SCREEN_H); // reset the window by drawing over it with white
        g.setColor(Color.BLUE);  // set color to blue
        g.fillRect(square_x, 50, 50, 50);  // draw square with correct coordinate and width/height of 50 px
    }
}