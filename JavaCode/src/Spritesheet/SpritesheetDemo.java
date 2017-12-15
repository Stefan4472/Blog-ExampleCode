package Spritesheet;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

// Shows JFrame window where spritesheet animation plays at 30FPS
public class SpritesheetDemo extends JFrame {

    private static final int DELAY = 33;        // number of ms delay between frames
    private TimedSpritesheet spritesheet;     // spritesheet to display frames for

    public SpritesheetDemo(TimedSpritesheet spritesheet) {
        this.spritesheet = spritesheet;
        // set dimensions to spritesheet frame size
        setSize(new Dimension(spritesheet.getFrameW(), spritesheet.getFrameH()));
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Spritesheet Display");
        setVisible(true);

        // set up an ActionListener to invalidate the window every DELAY milliseconds
        ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                repaint();  // repaint the screen
            }
        };
        new Timer(DELAY, taskPerformer).start();
    }

    // draws spritesheet's next frame to the window
    public void paint(Graphics g) {
        ((Graphics2D) g).drawImage(spritesheet.next(), null, 0, 0);
    }
}