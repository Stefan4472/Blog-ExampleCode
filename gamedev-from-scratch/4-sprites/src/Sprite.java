import java.awt.*;

// Parent class for all Sprites. Provides update() and draw() methods, as well as coordinate location.
public abstract class Sprite {

    // x- and y-coordinates of upper-left corder of the sprite. Use float for sub-pixel precision.
    protected float x, y;

    // constructor requiring only the coordinates of the sprite
    public Sprite(float x, float y) {
        this.x = x;
        this.y = y;
    }

    // updates the state of the sprite (implemented in subclass)
    abstract void update();

    // draws the sprite to the screen/graphics object (implemented in subclass)
    abstract void draw(Graphics2D g);
}