#include <stdio.h>
#include <stdlib.h>

// Coordinate in the grid
typedef struct {
  int x0, y0, x1, y1;
} GridLine;

// Grid dimensions and layout
#define GRID_COLS 4
#define GRID_ROWS 3
#define CELL_SIZE 5

// The grid data itself
#define GRID_DATA_LENGTH (GRID_COLS + GRID_ROWS)
GridLine gridLines[GRID_DATA_LENGTH];

void init_grid() {
  int max_x = (GRID_COLS - 1) * CELL_SIZE;
  int max_y = (GRID_ROWS - 1) * CELL_SIZE;
  int index = 0;

  for (int i = 0; i < (GRID_ROWS > GRID_COLS ? GRID_ROWS : GRID_COLS); i++) {
    if (i < GRID_ROWS) {
      int coord_y = i * CELL_SIZE;
      gridLines[index] = (GridLine){ .x0 = 0, .y0 = coord_y, .x1 = max_x, .y1 = coord_y };
      index++;
    }
    if (i < GRID_COLS) {
      int coord_x = i * CELL_SIZE;
      gridLines[index] = (GridLine){ .x0 = coord_x, .y0 = 0, .x1 = coord_x, .y1 = max_y };
      index++;
    }
  }
}

int main() {
  printf("Grid system initialized.\n\n");

  init_grid();
  for (int i = 0; i < GRID_DATA_LENGTH; i++) {
    printf("(%d, %d) and (%d, %d)\n",
        gridLines[i].x0,
        gridLines[i].y0,
        gridLines[i].x1,
        gridLines[i].y1);
  }

  return 0;
}

