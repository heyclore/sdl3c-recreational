#include "dry/sdl_app.h"

int q;

void initMessage() {
  printf("\n\n=== %s ===\n", "PRESS [Q] [W] [E] [A] [S] [D] KEY!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  SDL_Delay(66);
  return SDL_APP_CONTINUE;
}

float sqrtf(float x);
float atan2f(float y, float x);
float sinf(float x);
float cosf(float x);

#define PI 3.14159265359

#define COLOR 0xFFFF0000
#define WIDTH 640
#define HEIGHT 480
#define BACKGROUND_COLOR 0xFF181818
#define GRID_COUNT 4
#define GRID_PAD 0.5/GRID_COUNT
#define GRID_SIZE ((GRID_COUNT - 1)*GRID_PAD)
#define Z_START 0.25
#define DEG2RAD(deg) ((deg) * (PI / 180.0f))

static float angle = 0;
static float angle_step_deg = 15.0f;
void draw_point(int x, int y) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    ((uint32_t*)surface->pixels)[y * surface->w + x] = COLOR;
  }
}

void draw_line(int x0, int y0, int x1, int y1) {
  bool steep = abs(y1 - y0) > abs(x1 - x0);

  if (steep) {
    int temp = x0; x0 = y0; y0 = temp;
    temp = x1; x1 = y1; y1 = temp;
  }

  if (x0 > x1) {
    int temp = x0; x0 = x1; x1 = temp;
    temp = y0; y0 = y1; y1 = temp;
  }

  int dx = x1 - x0;
  int dy = abs(y1 - y0);
  int err = dx / 2;
  int ystep = (y0 < y1) ? 1 : -1;
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    if (steep) draw_point(y, x);
    else       draw_point(x, y);

    err -= dy;
    if (err < 0) {
      y += ystep;
      err += dx;
    }
  }
}

void foo(int reverse){
  SDL_memset(surface->pixels, 0x00, surface->w * surface->h * 4);

  if (reverse) angle -= DEG2RAD(angle_step_deg);
  else angle += DEG2RAD(angle_step_deg);

  for (int ix = 0; ix < GRID_COUNT; ++ix) {
    for (int iy = 0; iy < GRID_COUNT; ++iy) {
      for (int iz = 0; iz < GRID_COUNT; ++iz) {
        //printf("%d %d %d\n", ix,iy,iz);
      //if (iz > 2){ continue;}
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
        draw_point((x + 1)/2*WIDTH, (y + 1)/2*HEIGHT);
      }
    }
  }
  SDL_UpdateWindowSurface(window);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  float x,y;
  Uint32 buttons;
  buttons = SDL_GetMouseState(&x,&y);

  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
  }
  if (event->type == SDL_EVENT_KEY_DOWN) {
    if(q==0){
      //init_grid();
      //init_view();
      q++;
    }
    SDL_Scancode key_code = event->key.scancode;
    //printf("%u\n", key_code);

    switch (key_code) {
      case 26:
        foo(1);
        break;
      case 4:
        break;
      case 22:
        break;
      case 7:
        break;
      case 20:
        foo(0);
        break;
      case 8:
        break;
      default:
        break;
    }
  }
  return SDL_APP_CONTINUE;
}

