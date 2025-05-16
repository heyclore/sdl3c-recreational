/*
 * source = https://github.com/tsoding/olive.c/blob/master/demos/dots3d.c
 */
#include <stdint.h>
#include <stdio.h>

float sqrtf(float x);
float atan2f(float y, float x);
float sinf(float x);
float cosf(float x);
float dt = 0.016;

#define PI 3.14159265359

#define WIDTH 640
#define HEIGHT 480
#define BACKGROUND_COLOR 0xFF181818
#define GRID_COUNT 10
#define GRID_PAD 0.5/GRID_COUNT
#define GRID_SIZE ((GRID_COUNT - 1)*GRID_PAD)
#define CIRCLE_RADIUS 5
#define Z_START 0.25
#define ABOBA_PADDING 50

static uint32_t pixels[WIDTH*HEIGHT];
static float angle = 0;

int main()
{
  angle += 0.25*PI*dt;

  for (int ix = 0; ix < GRID_COUNT; ix++) {
    for (int iy = 0; iy < GRID_COUNT; iy++) {
      for (int iz = 0; iz < GRID_COUNT; iz++) {
        float x = ix*GRID_PAD - GRID_SIZE/2;
        float y = iy*GRID_PAD - GRID_SIZE/2;
        float z = Z_START + iz*GRID_PAD;

        float cx = 0.0;
        float cz = Z_START + GRID_SIZE/2;

        float dx = x - cx;
        float dz = z - cz;

        float a = atan2f(dz, dx);
        float m = sqrtf(dx*dx + dz*dz);

        dx = cosf(a + angle)*m;
        dz = sinf(a + angle)*m;

        x = dx + cx;
        z = dz + cz;

        x /= z;
        y /= z;

        uint32_t r = ix*255/GRID_COUNT;
        uint32_t g = iy*255/GRID_COUNT;
        uint32_t b = iz*255/GRID_COUNT;
        uint32_t color = 0xFF000000 | (r<<(0*8)) | (g<<(1*8)) | (b<<(2*8));
        printf("%f %f %d %u\n",(x + 1)/2*WIDTH, (y + 1)/2*HEIGHT, CIRCLE_RADIUS, color);
      }
    }
  }

  return 0;
}
