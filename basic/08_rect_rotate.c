#include "dry/sdl_app.h"

int q;

void initMessage() {
  printf("\n\n=== %s ===\n", "CLICK ON SCREEN & SEE THE IMAGE!!!");
  printf("=== %s ===\n\n", "CLICK ANY KEY TO SCREEN RESET!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate){
  SDL_Delay(66);
  return SDL_APP_CONTINUE;};

#define PI 3.1415926f
#define COLOR 0xFFFF0000

typedef struct {
  float x, y, z;
} Point3D;

void rotateX_around(Point3D *v, float cos_angle, float sin_angle, Point3D center) {
  v->y -= center.y;
  v->z -= center.z;

  float new_y = v->y * cos_angle - v->z * sin_angle;
  float new_z = v->y * sin_angle + v->z * cos_angle;

  v->y = new_y + center.y;
  v->z = new_z + center.z;
}
void rotateY_around(Point3D *v, float cos_angle, float sin_angle, Point3D center) {
  // Translate to origin (relative to center)
  v->x -= center.x;
  v->z -= center.z;

  // Rotate around Y axis
  float new_x = v->x * cos_angle + v->z * sin_angle;
  float new_z = -v->x * sin_angle + v->z * cos_angle;

  // Translate back
  v->x = new_x + center.x;
  v->z = new_z + center.z;
}
void rotateZ_around(Point3D *v, float cos_angle, float sin_angle, Point3D center) {
  v->x -= center.x;
  v->y -= center.y;

  float new_x = v->x * cos_angle - v->y * sin_angle;
  float new_y = v->x * sin_angle + v->y * cos_angle;

  v->x = new_x + center.x;
  v->y = new_y + center.y;
}



//Point3D points[] = {{10, 10, 0}, {20, 10, 0}, {10, 20, 0}, {20, 20, 0}};
//Point3D points[] = {{100, 100, 0}, {300, 100, 0}, {300, 300, 0}, {100, 300, 0}};
//Point3D center = {200, 200, 0};
Point3D points[] = {{100, 100, 0}, {300, 100, 0}, {300, 300, 0}, {100, 300, 0}};
Point3D center;
const char* pts[] = {"A", "B", "C", "D"};
//float angle = PI / 6.0f; // 30 degrees
float angle = PI / 18.0f; // 10 degrees
int num_points = sizeof(points) / sizeof(Point3D);
float cos_angle;
float sin_angle;

void draw_line(int x0, int y0, int x1, int y1, SDL_Surface *surface) {
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

  Uint32 *pixels = (Uint32 *)surface->pixels;
  // Iterate over the x values (fixed number of iterations from x0 to x1)
  for (int x = x0; x <= x1; x++) {
    // If the line is steep, swap the x and y coordinates when plotting
    if (steep) {
      //plot(y, x);  // Plot (y, x) if the line is steep
      //printf("Plotting pixel at (%d, %d)\n", y, x);
      pixels[y * surface->w + x] = COLOR;
    } else {
      //plot(x, y);  // Plot (x, y) if the line is normal
      pixels[x * surface->w + y] = COLOR;
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

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  if (event->type == SDL_EVENT_KEY_DOWN) {
    SDL_memset(surface->pixels, (0x000000 & 0xFF), surface->w * surface->h * 4);
    SDL_UpdateWindowSurface(window);
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if(q==0){
      center.x = abs(points[0].x - points[1].x);
      center.y = abs(points[1].y - points[2].y);
      center.z = 0;
      cos_angle = cosf(angle);
      sin_angle = sinf(angle);
      printf("Initial Points:\n");
      for (int i = 0; i < num_points; i++) {
        printf("%c: (%d, %d, %d)\n",
            'A' + i,
            (int)(points[i].x + 0.5f),
            (int)(points[i].y + 0.5f),
            (int)(points[i].z + 0.5f));
      }
    }
    // Rotate all four corners
    printf("Rotated Points:\n");
    for (int i = 0; i < num_points; i++) {
      //rotateY_around(&points[i], cos_angle, sin_angle, center);
      rotateZ_around(&points[i], cos_angle, sin_angle, center);
      printf("%c: (%d, %d, %d)\n",
          'A' + i,
          (int)(points[i].x + 0.5f),
          (int)(points[i].y + 0.5f),
          (int)(points[i].z + 0.5f));
    }
    SDL_memset(surface->pixels, (0x000000 & 0xFF), surface->w * surface->h * 4);
    for (int i = 0; i < num_points; i++) {
      int next = (i + 1) % num_points;

      if (points[i].y == points[next].y) {
        //printf("if %s to %s\n", pts[i], pts[next]);

        int x_start = (int)points[i].x;
        int x_end   = (int)points[next].x;
        int y       = (int)points[i].y;

        if (x_end < x_start) {
          int temp = x_start;
          x_start = x_end;
          x_end = temp;
        }

        int line_length = x_end - x_start + 1;

        Uint32 *pixels = (Uint32 *)surface->pixels;
        Uint32 *targetPixels = &pixels[y * surface->w + x_start];

        Uint32 colorBlock[line_length];
        for (int j = 0; j < line_length; ++j) {
          colorBlock[j] = COLOR;
        }

        SDL_memcpy(targetPixels, colorBlock, line_length * sizeof(Uint32));

      } else if (points[i].x == points[next].x) {
        int x = (int)points[i].x;
        int y_start = (int)points[i].y;
        int y_end   = (int)points[next].y;

        // Ensure y_start < y_end
        if (y_end < y_start) {
          int temp = y_start;
          y_start = y_end;
          y_end = temp;
        }

        Uint32 *pixels = (Uint32 *)surface->pixels;

        for (int y = y_start; y <= y_end; ++y) {
          pixels[y * surface->w + x] = COLOR;
        }
      } else {
        //printf("else %s to %s\n", pts[i], pts[next]);
        //printf("else %s: %d and %d\n", pts[i], (int)points[i].x, (int)points[i].y);
        //printf("else %s: %d and %d\n\n", pts[next], (int)points[next].x, (int)points[next].y);
        printf("Rotated Points:\n");
        draw_line((int)points[i].x, (int)points[i].y, (int)points[next].x, (int)points[next].y, surface);
      }
    }

    q++;
    SDL_UpdateWindowSurface(window);
  }
  return SDL_APP_CONTINUE;
}

