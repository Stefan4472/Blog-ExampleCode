import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        int[] frame_counts = { 4, 6, 10, 5 };
        Spritesheet spritesheet = new Spritesheet(loadImage("walking_front.png"), frame_counts);
        SpritesheetDemo demo = new SpritesheetDemo(spritesheet);
    }

    // utility method that reads an image file into memory given the file path. Returns BufferedImage.
    // raises IOException if file cannot be found
    public static BufferedImage loadImage(String path) throws IllegalArgumentException {
        try {
            return ImageIO.read(new File(path));
        } catch (IOException e) {
            throw new IllegalArgumentException("Could not find or read the file \'" + path + "\'"); // todo: use format
        }
    }
}