#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // For using the 'bool' type

void plot(int x, int y) {
  // Example implementation — replace this with actual drawing logic
  printf("Plotting pixel at (%d, %d)\n", x, y);
}

void draw_line_updated(int x0, int y0, int x1, int y1) {
  bool steep = abs(y1 - y0) > abs(x1 - x0);

  if (steep) {
    // Swap x and y
    int temp = x0;
    x0 = y0;
    y0 = temp;
    temp = x1;
    x1 = y1;
    y1 = temp;
  }

  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int err = dx / 2; // Initialize error to half of dx
  int ystep = (y0 < y1) ? 1 : -1; // Determine the direction of y-steps
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    if (steep) {
      plot(y, x);
    } else {
      plot(x, y);
    }

    err -= dy;
    if (err < 0) {
      y += ystep;
      err += dx;
    }
  }
}

int main() {
  // Example usage:
  draw_line_updated(10, 10, 32, 15);
  return 0;
}
