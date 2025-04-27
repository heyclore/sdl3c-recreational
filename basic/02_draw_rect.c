#include "dry/sdl_app.h"
#include <stdio.h>

int q;

void initMessage() {
  printf("\n\n=== %s ===\n\n", "CLICK ON SCREEN TO DRAW A RECTANGLE!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  SDL_Delay(666);
  return SDL_APP_CONTINUE;
}

void DrawRect(SDL_Surface* surface, int x, int y, int width, int height, uint8_t r, uint8_t g, uint8_t b){

  SDL_LockSurface(surface);

  for (int j = y; j < y + height; ++j) {
    for (int i = x; i < x + width; ++i) {
      // Check if the pixel is within the bounds of the surface
      if (i >= 0 && i < surface->w && j >= 0 && j < surface->h) {
        // Set the pixel color (r << 16) | (g << 8) | b for RGB
        ((uint32_t*)surface->pixels)[j * surface->w + i] = (r << 16) | (g << 8) | b;
      }
    }
  }

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
    DrawRect(surface, x, y, 30, 30, 255, 0, 0);
    SDL_UpdateWindowSurface(window);
  }
  return SDL_APP_CONTINUE;
}

