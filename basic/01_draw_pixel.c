#include "dry/sdl_app.h"
#include <stdio.h>

int q;

void initMessage() {
    printf("\n\n=== %s ===\n\n", "CLICK ON SCREEN TO DRAW A PIXEL!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  SDL_Delay(666);
  return SDL_APP_CONTINUE;
}

void SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){

  SDL_LockSurface(surface);
  uint8_t* pixelArray = (uint8_t*)surface->pixels;

  // Example of drawing a horizontal line at y = 300
  //int xStart = 10, xEnd = 70, yy = 30;

  ///*
  //   for (int r = xStart; r < xEnd; r++) {
  //   uint8_t *pixel = pixelArray + (yy * surface->w + r) * 4;
  //   pixel[0] = blue;
  //   pixel[1] = green;
  //   pixel[2] = red;
  //   pixel[3] = alpha;
  //   }
  uint32_t pixelValue = (r << 16) | (g << 8) | (b);
  *((uint32_t*)(pixelArray + (y * surface->w + x) * 4)) = pixelValue;

  SDL_UnlockSurface(surface);
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
    SetPixel(surface, x, y, 255, 0, 0);
    SDL_UpdateWindowSurface(window);
  }
  return SDL_APP_CONTINUE;
}

