#/*
gcc hello.c -lX11 && ./a.out; exit 0; */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>

#define WIN_W 100
#define WIN_H 100

typedef struct {
  Pixmap pm;
  int w, h;
  int dst_x, dst_y;
} Tile;

void init_titles(Display* d, Window w, GC gc, Tile* tiles, int count) {
  for (int i = 0; i < count; ++i) {
    XSetForeground(d, gc, 0x303030 * (i + 1));
    XFillRectangle(d, tiles[i].pm, gc, 0, 0, tiles[i].w, tiles[i].h);

    XCopyArea(d, tiles[i].pm, w, gc, 0, 0, tiles[i].w, tiles[i].h,
              tiles[i].dst_x, tiles[i].dst_y);
  }
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

  Tile tiles[3];

  tiles[0] = (Tile){
      XCreatePixmap(d, w, 80, 80, DefaultDepth(d, s)), 80, 80, 0, 0,
  };

  tiles[1] = (Tile){
      XCreatePixmap(d, w, 80, 20, DefaultDepth(d, s)), 80, 20, 0, 80,
  };

  tiles[2] =
      (Tile){XCreatePixmap(d, w, 20, 100, DefaultDepth(d, s)), 20, 100, 80, 0};

  XEvent e;

  while (1) {
    XNextEvent(d, &e);

    if (e.type == Expose) {
      init_titles(d, w, gc, tiles, 3);
    }

    if (e.type == KeyPress) {
      KeySym k = XLookupKeysym(&e.xkey, 0);
      if (k == XK_Escape) break;
    }
  }

  for (int i = 0; i < 3; i++) XFreePixmap(d, tiles[i].pm);

  XFreeGC(d, gc);
  XCloseDisplay(d);

  return 0;
}
