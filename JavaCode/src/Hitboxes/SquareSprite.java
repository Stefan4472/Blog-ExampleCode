package Hitboxes;

import java.awt.*;
import java.util.Random;

// A square with variable size and fill color that moves horizontally across the screen. Bounces
// off window edges, and changes color and direction when colliding with other sprites.
public class SquareSprite extends Sprite {

    // width of each side (px)
    private int width;
    // color to fill square
    private Color color;
    // width of the window the Square is on
    private int screenW;
    // pixels per frame the Square should travel along the x-axis
    private float speedX = 1;
    // used to generate random numbers
    private Random random = new Random();

    public SquareSprite(float x, float y, float speedX, int width, Color color, int screenW) {
        super(x, y, new Hitbox(x, y, width, width));
        this.width = width;
        this.color = color;
        this.screenW = screenW;
        this.speedX = speedX;
        hitbox = new Hitbox(x, y, width, width);  // initialize Hitbox with same dimensions
    }

    @Override
    void update() {
        // increment x-coordinate
        x += speedX;

        // check if we've hit the right edge of the screen
        if (x + width > screenW) {
            x = screenW - width;  // set to edge
            speedX *= -1;  // reverse speed
        } else if (x < 0) {  // check if we've hit the left edge of the canvas
            x = 0;  // set to edge
            speedX *= -1;  // reverse speed
        }

        // update hitbox coordinates to match sprite
        hitbox.set(x, y, width, width);
    }

    @Override
    void handleCollision(Sprite s) {
        // set a new color with random RGB
        color = new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256));
        // reverse speed
        speedX *= -1;
    }

    @Override
    void draw(Graphics2D g) {
        g.setColor(Color.RED);
        g.drawLine((int) x, (int) y, (int) (x + width), (int) (y + width));  // draw hitbox in red for demonstration
        g.setColor(color);  // set color: all three channels are color_int
        g.fillRect((int) x, (int) y, width, width);  // draw square with correct coordinate and width/height
    }
}
