#/*
gcc hello.c -lX11 && ./a.out; exit 0; */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define FACTOR_SIZE 5
#define WIN_W 100 * FACTOR_SIZE
#define WIN_H 100 * FACTOR_SIZE

typedef struct {
  Pixmap pm;
  int w, h;
  int dst_x, dst_y;
} Tile;

#define GRID 5
#define TILE_SIZE 3
int world_x = 1;
int world_y = 1;


void draw_map(Display* d, Window w, GC gc, Tile* map, int screen) {

    int cell_w = map->w / GRID;
    int cell_h = map->h / GRID;

    /* clear */
    XSetForeground(d, gc, BlackPixel(d, screen));
    XFillRectangle(d, map->pm, gc, 0, 0, map->w, map->h);

    /* center cell */
    int center_col = GRID / 2;
    int center_row = GRID / 2;

    /* draw grid */
    XSetForeground(d, gc, 0x555555);

    for (int i = 0; i <= GRID; i++) {
        XDrawLine(d, map->pm, gc,
                  i * cell_w, 0,
                  i * cell_w, map->h);

        XDrawLine(d, map->pm, gc,
                  0, i * cell_h,
                  map->w, i * cell_h);
    }

    /* draw player ALWAYS in center */
    XSetForeground(d, gc, WhitePixel(d, screen));

    int px = center_col * cell_w + cell_w / 4;
    int py = center_row * cell_h + cell_h / 4;

    XFillRectangle(d, map->pm, gc,
                   px, py,
                   cell_w / 2, cell_h / 2);

    /* copy to window */
    XCopyArea(d, map->pm, w, gc,
              0, 0, map->w, map->h,
              map->dst_x, map->dst_y);
}

int main() {
  Display* d = XOpenDisplay(NULL);
  int s = DefaultScreen(d);
  Window root = RootWindow(d, s);

  Window w = XCreateSimpleWindow(d, root, 0, 0, WIN_W, WIN_H, 0,
                                 BlackPixel(d, s), BlackPixel(d, s));

  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d, w);

  GC gc = XCreateGC(d, w, 0, NULL);

  int title_count = 1;
  Tile tiles[title_count];

  Tile ui_map= (Tile){
      XCreatePixmap(d, w, 20*FACTOR_SIZE, 20*FACTOR_SIZE, DefaultDepth(d, s)), 20*FACTOR_SIZE, 20*FACTOR_SIZE, 0*FACTOR_SIZE, 80*FACTOR_SIZE,
  };
  tiles[0] = ui_map;

  XEvent e;

  while (1) {
    XNextEvent(d, &e);

    if (e.type == Expose) {
      draw_map(d, w, gc, &ui_map, s);
    }

    if (e.type == KeyPress) {
      KeySym k = XLookupKeysym(&e.xkey, 0);

      if (k == XK_Escape || k == XK_F1)
        break;

      if (k == XK_w) world_y--;
      if (k == XK_s) world_y++;
      if (k == XK_a) world_x--;
      if (k == XK_d) world_x++;

      draw_map(d, w, gc, &ui_map, s);
    }
  }

  for (int i = 0; i < title_count; i++) XFreePixmap(d, tiles[i].pm);

  XFreeGC(d, gc);
  XCloseDisplay(d);

  return 0;
}
