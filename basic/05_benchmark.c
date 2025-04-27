#include "dry/sdl_app.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int q;

void initMessage() {
  printf("\n\n=== %s ===\n\n", "CLICK ON SCREEN & SEE THE LOG!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  SDL_Delay(666);
  return SDL_APP_CONTINUE;
}

void SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){
  int WIDTH = surface->w;
  int HEIGHT = surface->h;
  clock_t start, end;

  SDL_LockSurface(surface);

  start = clock();
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      ((uint32_t*)surface->pixels)[y * surface->w + x] = (r << 16) | (g << 8) | b;
    }
  }
  end = clock();

  SDL_UnlockSurface(surface);
  printf("Manual write time: %.5f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void MemSet(SDL_Surface* surface){
  Uint8 *pixels8 = (Uint8 *)surface->pixels;
  int WIDTH = surface->w;
  int HEIGHT = surface->h;
  Uint32 color = 0x12345678;
  clock_t start, end;

  start = clock();
  SDL_memset(pixels8, (color & 0xFF), WIDTH * HEIGHT * 4);
  end = clock();
  printf("SDL_memset   time: %.5f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void MemSet4(SDL_Surface* surface){
  Uint32 *pixels32 = (Uint32 *)surface->pixels;
  int WIDTH = surface->w;
  int HEIGHT = surface->h;
  Uint32 color = 0x00FF00FF;
  clock_t start, end;

  start = clock();
  SDL_memset4(pixels32, color, WIDTH * HEIGHT);
  end = clock();
  printf("SDL_memset4  time: %.5f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void Memcpy(SDL_Surface *surface) {
  Uint32 *pixels = (Uint32 *)surface->pixels;
  Uint32 *targetPixels = &pixels[0 * surface->w + 0];
  Uint32 color = 0xFF00FFFF;
  int WIDTH = surface->w;
  int HEIGHT = surface->h;
  clock_t start, end;

  start = clock();
  // Create a block of memory filled with the color
  Uint32 colorBlock[WIDTH];
  for (int i = 0; i < WIDTH; ++i) {
    colorBlock[i] = color;
  }

  // Copy the color block into the target region
  for (int i = 0; i < HEIGHT; ++i) {
    SDL_memcpy(&targetPixels[i * surface->w], colorBlock, WIDTH * sizeof(Uint32));
  }
  end = clock();
  printf("SDL_memcpy   time: %.5f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
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
    MemSet(surface);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(666);
    Memcpy(surface);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(666);
    MemSet4(surface);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(666);
    SetPixel(surface, x, y, 255, 0, 0);
    SDL_UpdateWindowSurface(window);
  }
  return SDL_APP_CONTINUE;
}

