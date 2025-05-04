#include <stdio.h>
#include <stdlib.h>

void plot(int x, int y) {
    // Example implementation — replace this with actual drawing logic
    printf("Plotting pixel at (%d, %d)\n", x, y);
}

void draw_line(int x0, int y0, int x1, int y1) {
    int steep = abs(y1 - y0) > abs(x1 - x0);

    // If the line is steep, swap x and y coordinates
    if (steep) {
        int temp = x0;
        x0 = y0;
        y0 = temp;
        
        temp = x1;
        x1 = y1;
        y1 = temp;
    }

    // If x0 > x1, swap the start and end points
    if (x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;

        int temp2 = y0;
        y0 = y1;
        y1 = temp2;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int delta_err = abs(dy) * 2;
    int err = 0;
    int y = y0;

    // Iterate over the x values (fixed number of iterations from x0 to x1)
    for (int x = x0; x <= x1; x++) {
        // If the line is steep, swap the x and y coordinates when plotting
        if (steep) {
            plot(y, x);  // Plot (y, x) if the line is steep
        } else {
            plot(x, y);  // Plot (x, y) if the line is normal
        }

        // Update the error term
        err += delta_err;

        // If the error term exceeds dx, adjust the y-coordinate
        if (err > dx) {  // Error exceeds the horizontal distance
            if (y0 < y1) {
                y++;  // Increment y if moving upwards
            } else {
                y--;  // Decrement y if moving downwards
            }
            err -= dx * 2;  // Subtract dx * 2 to reduce the error term
        }
    }
}

int main() {
    // Example usage:
    draw_line(10, 10, 32, 15);
    return 0;
}

