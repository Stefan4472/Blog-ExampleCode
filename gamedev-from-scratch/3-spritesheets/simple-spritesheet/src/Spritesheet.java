import java.awt.image.BufferedImage;

// Spritesheet that loops and displays each frame once
public class Spritesheet {

    private int counter = -1;       // current frame we're on (0-indexed)
    private int frameWidth, frameHeight;   // width and height of each frame (px)
    private int numFrames;          // number of frames in the sequence
    private BufferedImage img;      // the image itself

    // initialize with image and the number of frames it contains
    public Spritesheet(BufferedImage img, int numFrames) {
        this.img = img;
        frameWidth = img.getWidth() / numFrames;  // calculate width of each frame (px)
        frameHeight = img.getHeight();
        this.numFrames = numFrames;
    }

    // return the next frame in the sequence
    public BufferedImage next() {
        // increment counter. Use modulus to ensure it remains within the bounds of numFrames
        counter = (counter + 1) % numFrames;
        // return subimage containing the specified frame
        return img.getSubimage(counter * frameWidth, 0, frameWidth, frameHeight);
    }

    public int getFrameWidth() {
        return frameWidth;
    }

    public int getFrameHeight() {
        return frameHeight;
    }
}