import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;
import java.util.List;

// 400x400 window that demonstrates using several SquareSprites at once with hitboxes and collision detection.
public class HitboxDemo extends JFrame {

    private static final int DELAY = 33;        // number of ms delay between frames
    private List<Sprite> sprites;     // list of sprites on the screen

    public HitboxDemo() {
        // window set-up
        setSize(new Dimension(400, 400));
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Hitbox Demo");
        setVisible(true);

        // initialize some sprites and add them to the list
        sprites = new LinkedList<Sprite>();
        sprites.add(new SquareSprite(40, 90, 10.0f, 50, Color.BLUE, 400));
        sprites.add(new SquareSprite(200, 60, 14.4f, 30, Color.BLACK, 400));
        sprites.add(new SquareSprite(300, 300, 2.0f, 100, Color.ORANGE, 400));
        sprites.add(new SquareSprite(100, 250, 4.7f, 70, Color.GREEN, 400));

        // set up an ActionListener to invalidate the window every DELAY milliseconds
        ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                update();   // update all sprites
                repaint();  // repaint the screen
            }
        };
        new Timer(DELAY, taskPerformer).start();
    }

    // updates all sprites in the list
    public void update() {
        for (Sprite s : sprites) {
            s.update();
        }
        handleCollisions(sprites);
    }

    // checks each Sprite in the list against every other sprite and handles any collisions found
    // by calling the respective sprite's handleCollision() methods
    public void handleCollisions(List<Sprite> sprites) {
        for (int i = 0; i < sprites.size() - 1; i++) {
            for (int j = i + 1; j < sprites.size(); j++) {
                if (sprites.get(i).collides(sprites.get(j))) {
                    sprites.get(i).handleCollision(sprites.get(j));
                    sprites.get(j).handleCollision(sprites.get(i));
                }
            }
        }
    }

    // refreshes the screen by painting over it, then draws each sprite in the list
    public void paint(Graphics g) {
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, 400, 400);
        Graphics2D g2d = (Graphics2D) g;
        for (Sprite s : sprites) {
            s.draw(g2d);
        }
    }
}