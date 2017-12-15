package Spritesheet;

import java.awt.image.BufferedImage;

// Spritesheet that loops and displays each frame once
public class LoopingSpritesheet {

    private int counter = -1;       // current frame we're on (0-indexed)
    private int frame_w, frame_h;   // dimensions of frame (px)
    private int numFrames;          // number of frames in the sequence
    private BufferedImage img;      // the image itself

    // initialize with image and the number of frames it contains
    public LoopingSpritesheet(BufferedImage img, int numFrames) {
        this.img = img;
        frame_w = img.getWidth() / numFrames;  // calculate width of each sub-frame (px)
        frame_h = img.getHeight();
        this.numFrames = numFrames;
    }

    // return the next frame in the sequence
    public BufferedImage next() {
        // increment counter. Use modulus to ensure it remains within the bounds of numFrames
        counter = (counter + 1) % numFrames;
        // return frame's subimage
        return img.getSubimage(counter * frame_w, 0, frame_w, frame_h);
    }

    // return width of each frame in the spritesheet (px)
    public int getFrameW() {
        return frame_w;
    }

    // return height of each frame in the spritesheet (px)
    public int getFrameH() {
        return frame_h;
    }
}