import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

// 400x400 window that implements the Background class and KeyListener to let the user scroll across a background image
public class ScrollingBackgroundDemo extends JFrame implements KeyListener {

    private static final int DELAY = 33;        // number of ms delay between frames
    private Background background;

    // utility method that reads an image file into memory given the file path. Returns BufferedImage.
    // raises IllegalArgumentException if file cannot be found or read.
    public static BufferedImage loadImage(String path) throws IllegalArgumentException {
        try {
            return ImageIO.read(new File(path));
        } catch (IOException e) {
            throw new IllegalArgumentException("Could not find or read the file \'" + path + "\'");
        }
    }

    // constructor with no parameters: simply construct ScrollingBackgroundDemo to execute the code.
    public ScrollingBackgroundDemo() {
        // load background image and construct Background
        background = new Background(loadImage("world_map.png"), 400, 400);

        // window set-up
        setSize(new Dimension(400, 400));
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Scrolling Background Demo");
        setVisible(true);

        // IMPORTANT!! register a listener to this JFrame window
        addKeyListener(this);

        // set up an ActionListener to invalidate the window every DELAY milliseconds
        ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                repaint();  // repaint the screen
            }
        };

        // start the timer
        new Timer(DELAY, taskPerformer).start();
    }

    // refreshes the screen by painting over it, then draws the background
    public void paint(Graphics g) {
        background.draw(g);
    }

    @Override  // handle keyTyped action: we can ignore it, but still need it for the interface
    public void keyTyped(KeyEvent e) {

    }

    @Override  // handle keyPressed action: scroll Background accordingly
    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
            background.scroll(10, 0);  // right arrow key pressed: scroll +10 px along x
        } else if (e.getKeyCode() == KeyEvent.VK_LEFT) {
            background.scroll(-10, 0);  // left arrow key pressed: scroll -10 px along x
        } else if (e.getKeyCode() == KeyEvent.VK_UP) {
            background.scroll(0, -10);  // up arrow key pressed: scroll -10 px along y
        } else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
            background.scroll(0, 10);  // down arrow key pressed: scroll +10 px along y
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}