package Animation;

import javax.swing.*;
import java.awt.*;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
//import javax.swing.SwingUtilities;

public class Main {

    public static void main(String[] args) {
        new DrawBouncingSquare();
    }

    // displays a simple window with a canvas
    static class DrawingWindow extends JFrame {

        // color used to draw the square
        private static final Color GREEN = new Color(39, 100, 42);

        private int square_w = 50;                  // width of square edge (px)
        private int square_x = 50, square_y = 50;   // x- and y-coordinates of square's upper-left drawing point
        private int square_dx = 5;                  // number of pixels added to square_x each frame (to create motion)
        private static final int DELAY = 33;        // number of ms delay between frames
        private int screen_w, screen_h;                  // dimensions of window (px)

        public DrawingWindow(int width, int height) {
            screen_w = width;
            screen_h = height;
            setSize(new Dimension(width, height));
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            setTitle("Animation Example");
            setVisible(true);

            // set up an ActionListener to invalidate the window every DELAY milliseconds
            ActionListener taskPerformer = new ActionListener() {
                public void actionPerformed(ActionEvent evt) {
                    update();  // update position of square
                    repaint();  // repaint the screen
                }
            };

            new Timer(DELAY, taskPerformer).start();
        }

        // updates the square coordinates. Called each iteration of the loop
        public void update() {
            // increment x-coordinate
            square_x += square_dx;

            // check if we've hit the right edge of the canvas:
            // we have to our left x-coordinate and add the width of the square
            if (square_x + square_w > screen_w) {
                square_x = screen_w - square_w;  // set to edge
                square_dx *= -1;  // reverse speed
            } else if (square_x < 0) {  // check if we've hit the left edge of the canvas
                square_x = 0;  // set to edge
                square_dx *= -1;  // reverse speed
            }
        }

        // draws square to the canvas at the current coordinates with the color GREEN
        public void paint(Graphics g) {
            g.setColor(Color.WHITE);
            g.fillRect(0, 0, screen_w, screen_h);  // draw over the entire screen
            g.setColor(GREEN);  // set color to be used for drawing calls
            g.fillRect(square_x, square_y, square_w, square_w);  // draw the rectangle at the coordinates, with width/height
        }
    }
}