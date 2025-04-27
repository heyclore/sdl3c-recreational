#include "dry/sdl_app.h"
#include <stdio.h>

int j;

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", j);
  //SDL_Delay(1000);
  if (j < 10){
    j++;
  }
  if (j == 3){
    printf("%d\n", 1);
  }

  return SDL_APP_CONTINUE;
}

void SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){
  printf("%d\n", x);

  SDL_LockSurface(surface);
  uint8_t* pixelArray = (uint8_t*)surface->pixels;

  //uint8_t red = 128, green = 0, blue = 128, alpha = 0;

  //// Example of drawing a horizontal line at y = 300
  //int xStart = 10, xEnd = 70, yy = 30;

  ///*
  //   for (int r = xStart; r < xEnd; r++) {
  //   uint8_t *pixel = pixelArray + (yy * surface->w + r) * 4;
  //   pixel[0] = blue;
  //   pixel[1] = green;
  //   pixel[2] = red;
  //   pixel[3] = alpha;
  //   }
  //   */
  uint8_t *pixel = pixelArray + (y * surface->w + x) * 4;
  pixel[0] = b;
  pixel[1] = g;
  pixel[2] = r;
  pixel[3] = 0;

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
