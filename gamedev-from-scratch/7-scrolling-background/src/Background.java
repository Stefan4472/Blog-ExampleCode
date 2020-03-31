import java.awt.*;
import java.awt.image.BufferedImage;

// draws a scrollable background image. the "view pane" is the rectangular section of the background image currently
// being shown. use scroll() and centerOn() to shift the view pane, and draw() to draw the background to a Graphics
// object.
public class Background {

    // image used for the background
    private BufferedImage backgroundImg;
    // width and height of backgroundImg (px)
    private int backgroundW, backgroundH;
    // dimensions of the window/screen (should be smaller than size of backgroundImg)
    private int screenW, screenH;
    // current coordinates of top-left view pane
    private float x = 0, y = 0;

    // constructor that takes the full background image, as well as screen size
    public Background(BufferedImage backgroundImg, int screenW, int screenH) {
        this.backgroundImg = backgroundImg;
        this.screenW = screenW;
        this.screenH = screenH;
        backgroundW = backgroundImg.getWidth();
        backgroundH = backgroundImg.getHeight();
    }

    // scrolls the view pane by dx on the x-axis and dy on the y-axis, then restricts viewpane bounds
    public void scroll(float dx, float dy) {
        x += dx;
        y += dy;
        restrictBounds();
    }

    // centers the view pane on coordinates (x,y), then restricts viewpane bounds
    public void centerOn(float cx, float cy) {
        // calculate what new x and y coordinates should be to center on (cx,cy).
        x = cx - screenW / 2;
        y = cy - screenH / 2;
        restrictBounds();
    }

    // draws view pane subimage to Graphics object at (x,y)
    public void draw(Graphics g) {
        g.drawImage(backgroundImg, 0, 0, screenW, screenH, (int) x, (int) y, (int) (x + screenW), (int) (y + screenH), null);
    }

    // checks x- and y-coordinates, ensuring that the viewpane at that point would not go off the screen edge.
    // sets (x,y) to safe coordinates. should be executed before drawing takes place.
    private void restrictBounds() {
        // bounds check of horizontal screen edges
        if (x + screenW > backgroundW) {
            x = backgroundW - screenW;
        } else if (x < 0) {
            x = 0;
        }
        // bounds check of vertical screen edges
        if (y + screenH > backgroundH) {
            y = backgroundH - screenH;
        } else if (y < 0) {
            y = 0;
        }
    }
}