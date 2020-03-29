import java.awt.*;

// A square with variable size and fill color that moves horizontally across the screen and bouncess 
// off the edges.
public class SquareSprite extends Sprite {

    // width of each side (px)
    private int width;
    // color to fill square
    private Color color;
    // width of the window the Square is on
    private int screenW;
    // pixels per frame the Square should travel along the x-axis
    private float speedX = 1;

    public SquareSprite(float x, float y, float speedX, int width, Color color, int screenW) {
        super(x, y);
        this.width = width;
        this.color = color;
        this.screenW = screenW;
        this.speedX = speedX;
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
    }

    @Override
    void draw(Graphics2D g) {
        g.setColor(color);  // set color: all three channels are color_int
        g.fillRect((int) x, (int) y, width, width);  // draw square with correct coordinate and width/height
    }
}